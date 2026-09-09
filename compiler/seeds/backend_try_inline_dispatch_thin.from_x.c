/* seeds/backend_try_inline_dispatch_thin.from_x.c
 * G-02f backend_try_inline_dispatch R2 thin full surface (legacy name) — isomorphic with src/asm/backend_try_inline_dispatch_thin.x
 * Product PREFER_X_O: g05_try_x_to_o(thin.x) + full seed rest (-DXLANG_L2_TRY_INLINE_THIN_FROM_X) ld -r
 * Cap residual: *_impl / try_inline_* C 尾 outside thin (full seed rest)
 * Regen: ./xlang -E ... src/asm/backend_try_inline_dispatch_thin.x | filter DBG + polish externs
 */
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            include/poll.h and include/sys/uio.h shims also available.
 *            macOS/Linux delegate to system headers via #include_next.
 *            Historical #ifndef _WIN32 guard removed for safe includes. */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
extern int32_t glue_align_up8_c(int32_t n);
extern int32_t glue_is_vector_lane_scalar_binop_ko(int32_t ko);
extern int32_t glue_const_scalar_binop_eval_i32(int32_t binop_ko, int32_t a, int32_t b, int32_t * out);
extern int32_t asm_index_elem_byte_sz(uint8_t * arena, int32_t index_expr_ref);
extern int32_t asm_struct_lit_reserve_stack_bytes(uint8_t * arena, int32_t init_ref);
extern int32_t pipeline_asm_struct_lit_reserve_stack_bytes_c(uint8_t * arena, int32_t init_ref);
extern int32_t glue_enc_local_slot_ptr_or_addr(uint8_t * arena, uint8_t * elf_ctx, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx);
extern int32_t glue_arch_emit_local_slot_ptr_or_addr_text(uint8_t * arena, uint8_t * out, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx);
extern int32_t pipeline_asm_enc_local_slot_ptr_or_addr_elf_c(uint8_t * arena, uint8_t * elf_ctx, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx);
extern int32_t pipeline_asm_arch_emit_local_slot_ptr_or_addr_text_c(uint8_t * arena, uint8_t * out, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx);
extern int32_t glue_try_inline_local_slot_off(uint8_t * ctx, uint8_t * arena, uint8_t * name, int32_t name_len);
extern int32_t glue_try_fold_func_return_operand_ref(uint8_t * arena, uint8_t * mod, int32_t func_idx);
extern int32_t asm_array_lit_elem_byte_sz(uint8_t * arena, int32_t array_lit_ref);
extern int32_t asm_array_lit_reserve_stack_bytes(uint8_t * arena, int32_t init_ref);
extern int32_t pipeline_asm_array_lit_elem_byte_sz_c(uint8_t * arena, int32_t array_lit_ref);
extern int32_t pipeline_asm_array_lit_reserve_stack_bytes_c(uint8_t * arena, int32_t init_ref);
extern uint8_t * glue_asm_ctx_module_ref_c(uint8_t * asm_ctx);
extern int32_t glue_local_var_slot_holds_indirect_ptr(uint8_t * arena, int32_t expr_ref, uint8_t * asm_ctx);
extern int32_t glue_try_expr_const_i32(uint8_t * arena, int32_t expr_ref, int32_t * out);
extern int32_t glue_module_func_index_by_name(uint8_t * mod, uint8_t * name, int32_t name_len);
extern int32_t glue_module_named_type_has_struct_layout(uint8_t * mod, uint8_t * name, int32_t name_len);
extern int32_t glue_type_ref_is_named_struct_layout(uint8_t * arena, uint8_t * mod, int32_t ty_ref);
extern int32_t glue_expr_is_func_param_at(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t expr_ref, int32_t param_ix);
extern int32_t glue_struct_lit_field_index_by_name(uint8_t * arena, int32_t lit_ref, uint8_t * fn, int32_t fnlen);
extern int32_t glue_try_array_lit_lane_const_i32(uint8_t * arena, int32_t arr_ref, int32_t lane, int32_t * out);
extern int32_t glue_fold_func_returns_param0_index_const(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_lane);
extern int32_t glue_const_struct_lit_field_can_inline(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t lit_ref, int32_t fj);
extern int32_t glue_fold_func_returns_param01_scalar_binop(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_binop_ko);
extern int32_t glue_fold_func_returns_param_struct_lit(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_lit_ref);
extern int32_t glue_fold_func_returns_param01_vector_binop(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_binop_ko);
extern int32_t glue_call_is_zero_arg_default_alloc(uint8_t * arena, int32_t call_ref);
extern int32_t glue_dep_module_field_offset_by_name(uint8_t * pctx, uint8_t * field_name, int32_t flen);
extern int32_t glue_fold_func_returns_const_struct_lit(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_lit_ref);
extern int32_t glue_emit_default_alloc_to_rbx_offset(uint8_t * elf_ctx, int32_t foff, int32_t fsz, int32_t ta);
extern int32_t glue_inner_call_arg_for_field_access(uint8_t * arena, uint8_t * ctx, int32_t inner_call_ref, int32_t outer_field_ref, int32_t * out_arg_ref);
extern int32_t try_inline_wpo_const_scalar_binop_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t try_inline_x_plus_k_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t try_inline_param0_single_field_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t try_inline_wpo_const_vector_lane_of_binop_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t try_call_wpo_mono_symbol_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t glue_inline_var_field_access_offset(uint8_t * arena, uint8_t * mod, uint8_t * pctx, uint8_t * asm_ctx, int32_t fa_ref);
extern int32_t try_inline_param0_field_sum_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t try_call_wpo_mono_vector_lane_of_binop_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t glue_struct_lit_field_init_param_index(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t lit_ref, int32_t field_j, int32_t * out_param_ix);
extern int32_t try_inline_struct_lit_return_call_to_slot_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t call_ref, uint8_t * ctx, int32_t ta, int32_t stack_slot_off);
extern int32_t try_inline_const_struct_lit_return_call_to_slot_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t call_ref, uint8_t * ctx, int32_t ta, int32_t stack_slot_off);
extern int32_t glue_call_lookup_callee_mod_fi_arena(uint8_t * caller_arena, int32_t call_ref, uint8_t * ctx, uint8_t * out_ca, uint8_t * out_cm, int32_t * out_fi);
extern int32_t try_inline_var_field_sum_binop_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t left_ref, int32_t right_ref, uint8_t * ctx, int32_t ta);
extern int32_t glue_fold_func_return_operand_ref_module(uint8_t * arena, uint8_t * mod, int32_t func_idx);
extern int32_t asm_local_var_slot_holds_indirect_ptr(uint8_t * arena, int32_t expr_ref, uint8_t * mod_ref, uint8_t * asm_ctx);
extern int32_t pipeline_asm_index_elem_byte_sz(uint8_t * arena, int32_t index_expr_ref);
extern int32_t pipeline_expr_struct_lit_num_fields(uint8_t * arena, int32_t er);
int32_t glue_align_up8_c(int32_t n) {
  if (((n % 8) !=0)) {
    return (n + (8 - (n % 8)));
  }
  return n;
}
int32_t glue_is_vector_lane_scalar_binop_ko(int32_t ko) {
  if ((ko ==51)) {
    return 1;
  }
  if ((ko < 4)) {
    return 0;
  }
  if ((ko > 13)) {
    return 0;
  }
  return 1;
}
int32_t glue_const_scalar_binop_eval_i32(int32_t binop_ko, int32_t a, int32_t b, int32_t * out) {
  if ((out ==((int32_t *)(0)))) {
    return 0;
  }
  if ((binop_ko ==4)) {
    {
      (void)(((out)[0] = (a + b)));
    }
    return 1;
  }
  if ((binop_ko ==5)) {
    {
      (void)(((out)[0] = (a - b)));
    }
    return 1;
  }
  if ((binop_ko ==6)) {
    {
      (void)(((out)[0] = (a * b)));
    }
    return 1;
  }
  if ((binop_ko ==7)) {
    if ((b ==0)) {
      return 0;
    }
    {
      (void)(((out)[0] = (a / b)));
    }
    return 1;
  }
  if ((binop_ko ==8)) {
    if ((b ==0)) {
      return 0;
    }
    {
      (void)(((out)[0] = (a % b)));
    }
    return 1;
  }
  return 0;
}
int32_t asm_index_elem_byte_sz(uint8_t * arena, int32_t index_expr_ref) {
  {
    return pipeline_asm_index_elem_byte_sz(arena, index_expr_ref);
  }
  return 0;
}
int32_t asm_struct_lit_reserve_stack_bytes(uint8_t * arena, int32_t init_ref) {
  if ((arena ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((init_ref <=0)) {
    return 0;
  }
  {
    return (pipeline_expr_struct_lit_num_fields(arena, init_ref) * 8);
  }
  return 0;
}
int32_t pipeline_asm_struct_lit_reserve_stack_bytes_c(uint8_t * arena, int32_t init_ref) {
  if ((arena ==((uint8_t *)(0)))) {
    return 0;
  }
  if ((init_ref <=0)) {
    return 0;
  }
  {
    return (pipeline_expr_struct_lit_num_fields(arena, init_ref) * 8);
  }
  return 0;
}
extern int32_t glue_enc_local_slot_ptr_or_addr_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx);
extern int32_t glue_arch_emit_local_slot_ptr_or_addr_text_impl(uint8_t * arena, uint8_t * out, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx);
extern int32_t asm_ctx_local_find_offset_scoped(uint8_t * ctx, uint8_t * arena, uint8_t * name, int32_t nlen);
extern int32_t asm_ctx_local_find_offset(uint8_t * ctx, uint8_t * name, int32_t nlen);
extern int32_t backend_fold_func_return_operand_ref(uint8_t * arena, uint8_t * mod, int32_t func_idx);
extern int32_t glue_fold_func_return_operand_ref_module_impl(uint8_t * arena, uint8_t * mod, int32_t func_idx);
int32_t glue_enc_local_slot_ptr_or_addr(uint8_t * arena, uint8_t * elf_ctx, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx) {
  {
    return glue_enc_local_slot_ptr_or_addr_impl(arena, elf_ctx, arg_ref, slot_off, ta, asm_ctx);
  }
  return 0;
}
int32_t glue_arch_emit_local_slot_ptr_or_addr_text(uint8_t * arena, uint8_t * out, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx) {
  {
    return glue_arch_emit_local_slot_ptr_or_addr_text_impl(arena, out, arg_ref, slot_off, ta, asm_ctx);
  }
  return 0;
}
int32_t pipeline_asm_enc_local_slot_ptr_or_addr_elf_c(uint8_t * arena, uint8_t * elf_ctx, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx) {
  {
    return glue_enc_local_slot_ptr_or_addr_impl(arena, elf_ctx, arg_ref, slot_off, ta, asm_ctx);
  }
  return 0;
}
int32_t pipeline_asm_arch_emit_local_slot_ptr_or_addr_text_c(uint8_t * arena, uint8_t * out, int32_t arg_ref, int32_t slot_off, int32_t ta, uint8_t * asm_ctx) {
  {
    return glue_arch_emit_local_slot_ptr_or_addr_text_impl(arena, out, arg_ref, slot_off, ta, asm_ctx);
  }
  return 0;
}
int32_t glue_try_inline_local_slot_off(uint8_t * ctx, uint8_t * arena, uint8_t * name, int32_t name_len) {
  {
    if ((asm_ctx_local_find_offset_scoped(ctx, arena, name, name_len) >=0)) {
      return asm_ctx_local_find_offset_scoped(ctx, arena, name, name_len);
    }
    return asm_ctx_local_find_offset(ctx, name, name_len);
  }
  return (0 - 1);
}
int32_t glue_try_fold_func_return_operand_ref(uint8_t * arena, uint8_t * mod, int32_t func_idx) {
  {
    if ((backend_fold_func_return_operand_ref(arena, mod, func_idx) > 0)) {
      return backend_fold_func_return_operand_ref(arena, mod, func_idx);
    }
    return glue_fold_func_return_operand_ref_module_impl(arena, mod, func_idx);
  }
  return 0;
}
extern int32_t asm_array_lit_elem_byte_sz_impl(uint8_t * arena, int32_t array_lit_ref);
extern int32_t asm_array_lit_reserve_stack_bytes_impl(uint8_t * arena, int32_t init_ref);
int32_t asm_array_lit_elem_byte_sz(uint8_t * arena, int32_t array_lit_ref) {
  {
    return asm_array_lit_elem_byte_sz_impl(arena, array_lit_ref);
  }
  return 4;
}
int32_t asm_array_lit_reserve_stack_bytes(uint8_t * arena, int32_t init_ref) {
  {
    return asm_array_lit_reserve_stack_bytes_impl(arena, init_ref);
  }
  return 0;
}
/* wave143: Cap residual pure — definition in runtime_pipeline_abi */
int32_t pipeline_asm_array_lit_reserve_stack_bytes_c(uint8_t * arena, int32_t init_ref) {
  {
    return asm_array_lit_reserve_stack_bytes_impl(arena, init_ref);
  }
  return 0;
}
extern uint8_t * glue_asm_ctx_module_ref_c_impl(uint8_t * asm_ctx);
extern int32_t asm_local_var_slot_holds_indirect_ptr_impl(uint8_t * arena, int32_t expr_ref, uint8_t * mod_ref, uint8_t * asm_ctx);
extern int32_t backend_enc_load_rbp_to_rax_arch(uint8_t * elf_ctx, int32_t slot_off, int32_t ta);
extern int32_t backend_enc_lea_rbp_to_rax_arch(uint8_t * elf_ctx, int32_t slot_off, int32_t ta);
extern int32_t backend_arch_emit_load_rbp_to_rax(uint8_t * out, int32_t slot_off, int32_t ta);
extern int32_t backend_arch_emit_lea_rbp_to_rax(uint8_t * out, int32_t slot_off, int32_t ta);
uint8_t * glue_asm_ctx_module_ref_c(uint8_t * asm_ctx) {
  {
    return glue_asm_ctx_module_ref_c_impl(asm_ctx);
  }
  return ((uint8_t *)(0));
}
int32_t glue_local_var_slot_holds_indirect_ptr(uint8_t * arena, int32_t expr_ref, uint8_t * asm_ctx) {
  {
    return asm_local_var_slot_holds_indirect_ptr_impl(arena, expr_ref, glue_asm_ctx_module_ref_c(asm_ctx), asm_ctx);
  }
  return 0;
}
extern int32_t glue_try_expr_const_i32_impl(uint8_t * arena, int32_t expr_ref, int32_t * out);
int32_t glue_try_expr_const_i32(uint8_t * arena, int32_t expr_ref, int32_t * out) {
  {
    return glue_try_expr_const_i32_impl(arena, expr_ref, out);
  }
  return 0;
}
extern int32_t glue_module_func_index_by_name_impl(uint8_t * mod, uint8_t * name, int32_t name_len);
extern int32_t glue_module_named_type_has_struct_layout_impl(uint8_t * mod, uint8_t * name, int32_t name_len);
extern int32_t glue_type_ref_is_named_struct_layout_impl(uint8_t * arena, uint8_t * mod, int32_t ty_ref);
int32_t glue_module_func_index_by_name(uint8_t * mod, uint8_t * name, int32_t name_len) {
  {
    return glue_module_func_index_by_name_impl(mod, name, name_len);
  }
  return (0 - 1);
}
int32_t glue_module_named_type_has_struct_layout(uint8_t * mod, uint8_t * name, int32_t name_len) {
  {
    return glue_module_named_type_has_struct_layout_impl(mod, name, name_len);
  }
  return 0;
}
int32_t glue_type_ref_is_named_struct_layout(uint8_t * arena, uint8_t * mod, int32_t ty_ref) {
  {
    return glue_type_ref_is_named_struct_layout_impl(arena, mod, ty_ref);
  }
  return 0;
}
extern int32_t glue_expr_is_func_param_at_impl(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t expr_ref, int32_t param_ix);
extern int32_t glue_struct_lit_field_index_by_name_impl(uint8_t * arena, int32_t lit_ref, uint8_t * fn, int32_t fnlen);
extern int32_t glue_try_array_lit_lane_const_i32_impl(uint8_t * arena, int32_t arr_ref, int32_t lane, int32_t * out);
int32_t glue_expr_is_func_param_at(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t expr_ref, int32_t param_ix) {
  {
    return glue_expr_is_func_param_at_impl(arena, mod, func_idx, expr_ref, param_ix);
  }
  return 0;
}
int32_t glue_struct_lit_field_index_by_name(uint8_t * arena, int32_t lit_ref, uint8_t * fn, int32_t fnlen) {
  {
    return glue_struct_lit_field_index_by_name_impl(arena, lit_ref, fn, fnlen);
  }
  return (0 - 1);
}
int32_t glue_try_array_lit_lane_const_i32(uint8_t * arena, int32_t arr_ref, int32_t lane, int32_t * out) {
  {
    return glue_try_array_lit_lane_const_i32_impl(arena, arr_ref, lane, out);
  }
  return 0;
}
extern int32_t glue_fold_func_returns_param0_index_const_impl(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_lane);
extern int32_t glue_const_struct_lit_field_can_inline_impl(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t lit_ref, int32_t fj);
extern int32_t glue_fold_func_returns_param01_scalar_binop_impl(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_binop_ko);
int32_t glue_fold_func_returns_param0_index_const(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_lane) {
  {
    return glue_fold_func_returns_param0_index_const_impl(arena, mod, func_idx, out_lane);
  }
  return 0;
}
int32_t glue_const_struct_lit_field_can_inline(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t lit_ref, int32_t fj) {
  {
    return glue_const_struct_lit_field_can_inline_impl(arena, mod, func_idx, lit_ref, fj);
  }
  return 0;
}
int32_t glue_fold_func_returns_param01_scalar_binop(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_binop_ko) {
  {
    return glue_fold_func_returns_param01_scalar_binop_impl(arena, mod, func_idx, out_binop_ko);
  }
  return 0;
}
extern int32_t glue_fold_func_returns_param_struct_lit_impl(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_lit_ref);
extern int32_t glue_fold_func_returns_param01_vector_binop_impl(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_binop_ko);
extern int32_t glue_call_is_zero_arg_default_alloc_impl(uint8_t * arena, int32_t call_ref);
int32_t glue_fold_func_returns_param_struct_lit(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_lit_ref) {
  {
    return glue_fold_func_returns_param_struct_lit_impl(arena, mod, func_idx, out_lit_ref);
  }
  return 0;
}
int32_t glue_fold_func_returns_param01_vector_binop(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_binop_ko) {
  {
    return glue_fold_func_returns_param01_vector_binop_impl(arena, mod, func_idx, out_binop_ko);
  }
  return 0;
}
int32_t glue_call_is_zero_arg_default_alloc(uint8_t * arena, int32_t call_ref) {
  {
    return glue_call_is_zero_arg_default_alloc_impl(arena, call_ref);
  }
  return 0;
}
extern int32_t glue_dep_module_field_offset_by_name_impl(uint8_t * pctx, uint8_t * field_name, int32_t flen);
extern int32_t glue_fold_func_returns_const_struct_lit_impl(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_lit_ref);
extern int32_t glue_emit_default_alloc_to_rbx_offset_impl(uint8_t * elf_ctx, int32_t foff, int32_t fsz, int32_t ta);
int32_t glue_dep_module_field_offset_by_name(uint8_t * pctx, uint8_t * field_name, int32_t flen) {
  {
    return glue_dep_module_field_offset_by_name_impl(pctx, field_name, flen);
  }
  return (0 - 1);
}
int32_t glue_fold_func_returns_const_struct_lit(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t * out_lit_ref) {
  {
    return glue_fold_func_returns_const_struct_lit_impl(arena, mod, func_idx, out_lit_ref);
  }
  return 0;
}
int32_t glue_emit_default_alloc_to_rbx_offset(uint8_t * elf_ctx, int32_t foff, int32_t fsz, int32_t ta) {
  {
    return glue_emit_default_alloc_to_rbx_offset_impl(elf_ctx, foff, fsz, ta);
  }
  return (0 - 1);
}
extern int32_t glue_inner_call_arg_for_field_access_impl(uint8_t * arena, uint8_t * ctx, int32_t inner_call_ref, int32_t outer_field_ref, int32_t * out_arg_ref);
extern int32_t try_inline_wpo_const_scalar_binop_call_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t try_inline_x_plus_k_call_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
int32_t glue_inner_call_arg_for_field_access(uint8_t * arena, uint8_t * ctx, int32_t inner_call_ref, int32_t outer_field_ref, int32_t * out_arg_ref) {
  {
    return glue_inner_call_arg_for_field_access_impl(arena, ctx, inner_call_ref, outer_field_ref, out_arg_ref);
  }
  return 0;
}
int32_t try_inline_wpo_const_scalar_binop_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta) {
  {
    return try_inline_wpo_const_scalar_binop_call_elf_impl(arena, elf_ctx, expr_ref, ctx, ta);
  }
  return 0;
}
int32_t try_inline_x_plus_k_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta) {
  {
    return try_inline_x_plus_k_call_elf_impl(arena, elf_ctx, expr_ref, ctx, ta);
  }
  return 0;
}
extern int32_t try_inline_param0_single_field_call_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t try_inline_wpo_const_vector_lane_of_binop_call_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t try_call_wpo_mono_symbol_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
int32_t try_inline_param0_single_field_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta) {
  {
    return try_inline_param0_single_field_call_elf_impl(arena, elf_ctx, expr_ref, ctx, ta);
  }
  return 0;
}
int32_t try_inline_wpo_const_vector_lane_of_binop_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta) {
  {
    return try_inline_wpo_const_vector_lane_of_binop_call_elf_impl(arena, elf_ctx, expr_ref, ctx, ta);
  }
  return 0;
}
int32_t try_call_wpo_mono_symbol_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta) {
  {
    return try_call_wpo_mono_symbol_elf_impl(arena, elf_ctx, expr_ref, ctx, ta);
  }
  return 0;
}
extern int32_t glue_inline_var_field_access_offset_impl(uint8_t * arena, uint8_t * mod, uint8_t * pctx, uint8_t * asm_ctx, int32_t fa_ref);
extern int32_t try_inline_param0_field_sum_call_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
extern int32_t try_call_wpo_mono_vector_lane_of_binop_call_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta);
int32_t glue_inline_var_field_access_offset(uint8_t * arena, uint8_t * mod, uint8_t * pctx, uint8_t * asm_ctx, int32_t fa_ref) {
  {
    return glue_inline_var_field_access_offset_impl(arena, mod, pctx, asm_ctx, fa_ref);
  }
  return (0 - 1);
}
int32_t try_inline_param0_field_sum_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta) {
  {
    return try_inline_param0_field_sum_call_elf_impl(arena, elf_ctx, expr_ref, ctx, ta);
  }
  return 0;
}
int32_t try_call_wpo_mono_vector_lane_of_binop_call_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t expr_ref, uint8_t * ctx, int32_t ta) {
  {
    return try_call_wpo_mono_vector_lane_of_binop_call_elf_impl(arena, elf_ctx, expr_ref, ctx, ta);
  }
  return 0;
}
extern int32_t glue_struct_lit_field_init_param_index_impl(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t lit_ref, int32_t field_j, int32_t * out_param_ix);
extern int32_t try_inline_struct_lit_return_call_to_slot_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t call_ref, uint8_t * ctx, int32_t ta, int32_t stack_slot_off);
extern int32_t try_inline_const_struct_lit_return_call_to_slot_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t call_ref, uint8_t * ctx, int32_t ta, int32_t stack_slot_off);
int32_t glue_struct_lit_field_init_param_index(uint8_t * arena, uint8_t * mod, int32_t func_idx, int32_t lit_ref, int32_t field_j, int32_t * out_param_ix) {
  {
    return glue_struct_lit_field_init_param_index_impl(arena, mod, func_idx, lit_ref, field_j, out_param_ix);
  }
  return (0 - 1);
}
int32_t try_inline_struct_lit_return_call_to_slot_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t call_ref, uint8_t * ctx, int32_t ta, int32_t stack_slot_off) {
  {
    return try_inline_struct_lit_return_call_to_slot_elf_impl(arena, elf_ctx, call_ref, ctx, ta, stack_slot_off);
  }
  return 0;
}
int32_t try_inline_const_struct_lit_return_call_to_slot_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t call_ref, uint8_t * ctx, int32_t ta, int32_t stack_slot_off) {
  {
    return try_inline_const_struct_lit_return_call_to_slot_elf_impl(arena, elf_ctx, call_ref, ctx, ta, stack_slot_off);
  }
  return 0;
}
extern int32_t glue_call_lookup_callee_mod_fi_arena_impl(uint8_t * caller_arena, int32_t call_ref, uint8_t * ctx, uint8_t * out_ca, uint8_t * out_cm, int32_t * out_fi);
extern int32_t try_inline_var_field_sum_binop_elf_impl(uint8_t * arena, uint8_t * elf_ctx, int32_t left_ref, int32_t right_ref, uint8_t * ctx, int32_t ta);
int32_t glue_call_lookup_callee_mod_fi_arena(uint8_t * caller_arena, int32_t call_ref, uint8_t * ctx, uint8_t * out_ca, uint8_t * out_cm, int32_t * out_fi) {
  {
    return glue_call_lookup_callee_mod_fi_arena_impl(caller_arena, call_ref, ctx, out_ca, out_cm, out_fi);
  }
  return 0;
}
int32_t try_inline_var_field_sum_binop_elf(uint8_t * arena, uint8_t * elf_ctx, int32_t left_ref, int32_t right_ref, uint8_t * ctx, int32_t ta) {
  {
    return try_inline_var_field_sum_binop_elf_impl(arena, elf_ctx, left_ref, right_ref, ctx, ta);
  }
  return 0;
}
int32_t glue_fold_func_return_operand_ref_module(uint8_t * arena, uint8_t * mod, int32_t func_idx) {
  {
    return glue_fold_func_return_operand_ref_module_impl(arena, mod, func_idx);
  }
  return 0;
}
int32_t asm_local_var_slot_holds_indirect_ptr(uint8_t * arena, int32_t expr_ref, uint8_t * mod_ref, uint8_t * asm_ctx) {
  {
    return asm_local_var_slot_holds_indirect_ptr_impl(arena, expr_ref, mod_ref, asm_ctx);
  }
  return 0;
}
