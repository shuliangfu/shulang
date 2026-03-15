/**
 * std/channel/channel.c — 有界/无界 channel（对标 Rust std::sync::mpsc、Zig 无标准 channel）
 *
 * 【文件职责】
 * 实现 std.channel 的 C 层：channel_i32_bounded、channel_i32_unbounded、send、recv、try_recv、close、free。
 * 有界：固定容量，send 满时阻塞；无界：缓冲区按需增长。使用 mutex + condition variable。
 *
 * 【所属模块/组件】
 * 标准库 std.channel；与 std/channel/mod.su 同属一模块。依赖 std.heap（malloc/realloc/free）；Unix 需 -lpthread。
 */

#include <stdint.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
/* Windows：暂用 stub，返回 NULL / -1；完整实现可用 CRITICAL_SECTION + CONDITION_VARIABLE。 */
static const int32_t CHAN_ERR_CLOSED = -1;
static const int32_t CHAN_ERR_FULL = 1;
static const int32_t CHAN_ERR_EMPTY = 1;

void *channel_i32_bounded_c(int32_t cap) {
    (void)cap;
    return NULL;
}
void *channel_i32_unbounded_c(void) { return NULL; }
int32_t channel_i32_send_c(void *ch, int32_t val) {
    (void)ch; (void)val;
    return CHAN_ERR_CLOSED;
}
int32_t channel_i32_recv_c(void *ch, int32_t *out) {
    (void)ch; (void)out;
    return CHAN_ERR_CLOSED;
}
int32_t channel_i32_try_send_c(void *ch, int32_t val) {
    (void)ch; (void)val;
    return CHAN_ERR_CLOSED;
}
int32_t channel_i32_try_recv_c(void *ch, int32_t *out) {
    (void)ch; (void)out;
    return CHAN_ERR_CLOSED;
}
void channel_i32_close_c(void *ch) { (void)ch; }
void channel_i32_free_c(void *ch) { (void)ch; }

#else
#include <pthread.h>

#define CHAN_ERR_CLOSED (-1)
#define CHAN_ERR_FULL   1
#define CHAN_ERR_EMPTY  1
#define UNBOUNDED_INIT_CAP 16

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t  cond_not_empty;
    pthread_cond_t  cond_not_full;
    int32_t        *buf;
    int32_t         cap;    /* 有界为固定容量；无界为当前缓冲区大小，满时翻倍 */
    int32_t         len;
    int32_t         head;   /* 环形：下一个取的位置 */
    int32_t         closed; /* 1 已关闭 */
    int32_t         unbounded; /* 1 无界，可扩容 */
} channel_i32_impl_t;

/** 有界 channel：容量 cap，send 满时阻塞。返回句柄或 NULL。 */
void *channel_i32_bounded_c(int32_t cap) {
    if (cap <= 0) return NULL;
    channel_i32_impl_t *ch = (channel_i32_impl_t *)malloc(sizeof(channel_i32_impl_t));
    if (!ch) return NULL;
    ch->buf = (int32_t *)malloc((size_t)cap * sizeof(int32_t));
    if (!ch->buf) { free(ch); return NULL; }
    ch->cap = cap;
    ch->len = 0;
    ch->head = 0;
    ch->closed = 0;
    ch->unbounded = 0;
    if (pthread_mutex_init(&ch->mutex, NULL) != 0) { free(ch->buf); free(ch); return NULL; }
    if (pthread_cond_init(&ch->cond_not_empty, NULL) != 0) { pthread_mutex_destroy(&ch->mutex); free(ch->buf); free(ch); return NULL; }
    if (pthread_cond_init(&ch->cond_not_full, NULL) != 0) { pthread_cond_destroy(&ch->cond_not_empty); pthread_mutex_destroy(&ch->mutex); free(ch->buf); free(ch); return NULL; }
    return (void *)ch;
}

/** 无界 channel：send 不因满而阻塞，内部按需扩容。 */
void *channel_i32_unbounded_c(void) {
    channel_i32_impl_t *ch = (channel_i32_impl_t *)malloc(sizeof(channel_i32_impl_t));
    if (!ch) return NULL;
    ch->buf = (int32_t *)malloc((size_t)UNBOUNDED_INIT_CAP * sizeof(int32_t));
    if (!ch->buf) { free(ch); return NULL; }
    ch->cap = UNBOUNDED_INIT_CAP;
    ch->len = 0;
    ch->head = 0;
    ch->closed = 0;
    ch->unbounded = 1;
    if (pthread_mutex_init(&ch->mutex, NULL) != 0) { free(ch->buf); free(ch); return NULL; }
    if (pthread_cond_init(&ch->cond_not_empty, NULL) != 0) { pthread_mutex_destroy(&ch->mutex); free(ch->buf); free(ch); return NULL; }
    if (pthread_cond_init(&ch->cond_not_full, NULL) != 0) { pthread_cond_destroy(&ch->cond_not_empty); pthread_mutex_destroy(&ch->mutex); free(ch->buf); free(ch); return NULL; }
    return (void *)ch;
}

/** 发送 val；有界且满时阻塞直到有空间。返回 0 成功，-1 已关闭。 */
int32_t channel_i32_send_c(void *ch, int32_t val) {
    if (!ch) return CHAN_ERR_CLOSED;
    channel_i32_impl_t *c = (channel_i32_impl_t *)ch;
    pthread_mutex_lock(&c->mutex);
    if (c->closed) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_CLOSED; }
    if (c->unbounded) {
        while (c->len == c->cap) {
            int32_t new_cap = c->cap * 2;
            if (new_cap <= c->cap) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_CLOSED; }
            int32_t *n = (int32_t *)realloc(c->buf, (size_t)new_cap * sizeof(int32_t));
            if (!n) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_CLOSED; }
            /* 将 [head..head+len) 搬到连续 [0..len) */
            int32_t i, j;
            for (i = 0, j = c->head; i < c->len; i++, j = (j + 1) % c->cap)
                n[i] = c->buf[j];
            free(c->buf);
            c->buf = n;
            c->cap = new_cap;
            c->head = 0;
        }
    } else {
        while (c->len == c->cap) {
            pthread_cond_wait(&c->cond_not_full, &c->mutex);
            if (c->closed) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_CLOSED; }
        }
    }
    c->buf[(c->head + c->len) % c->cap] = val;
    c->len++;
    pthread_cond_signal(&c->cond_not_empty);
    pthread_mutex_unlock(&c->mutex);
    return 0;
}

/** 接收：阻塞直到有值或已关闭。*out 写入值；返回 0 成功，-1 已关闭且无数据。 */
int32_t channel_i32_recv_c(void *ch, int32_t *out) {
    if (!ch || !out) return CHAN_ERR_CLOSED;
    channel_i32_impl_t *c = (channel_i32_impl_t *)ch;
    pthread_mutex_lock(&c->mutex);
    while (c->len == 0) {
        if (c->closed) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_CLOSED; }
        pthread_cond_wait(&c->cond_not_empty, &c->mutex);
    }
    *out = c->buf[c->head];
    c->head = (c->head + 1) % c->cap;
    c->len--;
    pthread_cond_signal(&c->cond_not_full);
    pthread_mutex_unlock(&c->mutex);
    return 0;
}

/** 非阻塞发送。返回 0 成功，1 满（有界），-1 已关闭。 */
int32_t channel_i32_try_send_c(void *ch, int32_t val) {
    if (!ch) return CHAN_ERR_CLOSED;
    channel_i32_impl_t *c = (channel_i32_impl_t *)ch;
    pthread_mutex_lock(&c->mutex);
    if (c->closed) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_CLOSED; }
    if (c->unbounded) {
        if (c->len == c->cap) {
            int32_t new_cap = c->cap * 2;
            if (new_cap <= c->cap) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_CLOSED; }
            int32_t *n = (int32_t *)realloc(c->buf, (size_t)new_cap * sizeof(int32_t));
            if (!n) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_CLOSED; }
            int32_t i, j;
            for (i = 0, j = c->head; i < c->len; i++, j = (j + 1) % c->cap) n[i] = c->buf[j];
            free(c->buf); c->buf = n; c->cap = new_cap; c->head = 0;
        }
    } else if (c->len == c->cap) {
        pthread_mutex_unlock(&c->mutex);
        return CHAN_ERR_FULL;
    }
    c->buf[(c->head + c->len) % c->cap] = val;
    c->len++;
    pthread_cond_signal(&c->cond_not_empty);
    pthread_mutex_unlock(&c->mutex);
    return 0;
}

/** 非阻塞接收。返回 0 成功 *out 有效，1 空，-1 已关闭。 */
int32_t channel_i32_try_recv_c(void *ch, int32_t *out) {
    if (!ch || !out) return CHAN_ERR_CLOSED;
    channel_i32_impl_t *c = (channel_i32_impl_t *)ch;
    pthread_mutex_lock(&c->mutex);
    if (c->closed && c->len == 0) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_CLOSED; }
    if (c->len == 0) { pthread_mutex_unlock(&c->mutex); return CHAN_ERR_EMPTY; }
    *out = c->buf[c->head];
    c->head = (c->head + 1) % c->cap;
    c->len--;
    pthread_cond_signal(&c->cond_not_full);
    pthread_mutex_unlock(&c->mutex);
    return 0;
}

void channel_i32_close_c(void *ch) {
    if (!ch) return;
    channel_i32_impl_t *c = (channel_i32_impl_t *)ch;
    pthread_mutex_lock(&c->mutex);
    c->closed = 1;
    pthread_cond_broadcast(&c->cond_not_empty);
    pthread_cond_broadcast(&c->cond_not_full);
    pthread_mutex_unlock(&c->mutex);
}

void channel_i32_free_c(void *ch) {
    if (!ch) return;
    channel_i32_impl_t *c = (channel_i32_impl_t *)ch;
    pthread_mutex_destroy(&c->mutex);
    pthread_cond_destroy(&c->cond_not_empty);
    pthread_cond_destroy(&c->cond_not_full);
    free(c->buf);
    free(c);
}
#endif
