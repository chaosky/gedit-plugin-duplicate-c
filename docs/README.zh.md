# Gedit 行复制插件 (C)

**其他语言:** [English](../README.md) · [日本語](README.ja.md) · [Русский](README.ru.md) · [Français](README.fr.md) · [Español](README.es.md) · [Português](README.pt.md) · [Italiano](README.it.md) · [한국어](README.ko.md)

一个 gedit 插件，用于复制当前行、当前选区或选中的多行。用 C 为 gedit 49+ 重写（该版本[不再支持 Python 插件](https://gedit-text-editor.org/blog/2025-04-30-no-more-pythons-in-gedit.html)）。

基于 [hannenz/duplicate](https://github.com/hannenz/duplicate) 改写。

## 默认快捷键

`Ctrl+Shift+D` — 复制行/选区

## 构建

需要 `gedit-devel` 和 `meson`：

```bash
# Fedora
sudo dnf install gedit-devel meson

# 构建
meson setup builddir
meson compile -C builddir
```

## 安装

将 `.so` 和 `.plugin` 文件复制到 gedit 的插件目录：

```bash
cp builddir/libduplicateline.so duplicateline.plugin ~/.local/share/gedit/plugins/
```

然后在 gedit → 首选项 → 插件 中启用 "Duplicate Line"。

## 故障排查

### `libgedit-49.so: cannot open shared object file: No such file or directory`

如果 gedit 升级后插件无法加载，并看到类似信息：

```
Failed to load module 'duplicateline': libgedit-49.so: cannot open shared object file: No such file or directory
Error loading plugin 'duplicateline'
```

这是 **gedit 大版本升级后的预期现象**。编译出的 `.so` 链接的是构建时所安装的那个具体 `libgedit-<N>.so`（例如 gedit 49 对应 `libgedit-49.so`）。当 gedit 升级（例如升到 50）后，旧库被删除，插件就找不到它了。

**解决办法：重新针对新版 gedit 编译并重装即可。**

```bash
rm -rf builddir
meson setup builddir
meson compile -C builddir
cp builddir/libduplicateline.so ~/.local/share/gedit/plugins/
```

然后重启 gedit。每次 gedit 大版本升级后做一次即可。

## 修改快捷键

编辑 `duplicateline.c`，找到：

```c
const gchar *accels[] = { "<Primary><Shift>d", NULL };
```

替换为你想要的按键组合，然后重新构建并安装。示例：
- `<Primary><Shift>d` → Ctrl+Shift+D
- `<Alt>d` → Alt+D
- `<Primary>d` → Ctrl+D

## 许可证

GPL-2.0-or-later
