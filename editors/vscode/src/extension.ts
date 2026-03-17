/**
 * Shulang VSCode 扩展入口 — LSP 客户端
 *
 * 在打开 .su 文件时激活，启动 shu --lsp 作为 Language Server（stdio），
 * 提供：诊断（P1）、跳转定义 / 查找引用 / 悬停（P2）。
 * 语法高亮与语言配置由 package.json 静态贡献，无需在此处理。
 */

import * as path from 'path';
import { workspace, ExtensionContext } from 'vscode';
import {
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
} from 'vscode-languageclient/node';

let client: LanguageClient | undefined;

/**
 * 解析 shu 可执行路径：若为相对路径则相对于工作区根目录解析为绝对路径；
 * 若为不含路径分隔符的名称（如 shu）则原样返回，依赖 PATH 查找。
 */
function resolveServerCommand(configured: string): string {
  if (path.isAbsolute(configured)) {
    return configured;
  }
  const root = workspace.workspaceFolders?.[0]?.uri.fsPath;
  if (root && configured.includes(path.sep)) {
    return path.join(root, configured);
  }
  return configured;
}

export function activate(context: ExtensionContext): void {
  const config = workspace.getConfiguration('shulang');
  const serverPath = config.get<string>('serverPath', 'shu');
  const command = resolveServerCommand(serverPath);

  const serverOptions: ServerOptions = {
    command,
    args: ['--lsp'],
    options: {
      cwd: workspace.workspaceFolders?.[0]?.uri.fsPath,
    },
  };

  const clientOptions: LanguageClientOptions = {
    documentSelector: [{ scheme: 'file', language: 'su' }],
    synchronize: {
      fileEvents: workspace.createFileSystemWatcher('**/*.su'),
    },
  };

  client = new LanguageClient(
    'shulang',
    'Shulang Language Server',
    serverOptions,
    clientOptions
  );

  client.start();
}

export function deactivate(): Thenable<void> | undefined {
  return client?.stop();
}
