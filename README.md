# Gedit Duplicate Line Plugin (C)

**Read this in other languages:** [日本語](docs/README.ja.md) · [中文](docs/README.zh.md) · [Русский](docs/README.ru.md) · [Français](docs/README.fr.md) · [Español](docs/README.es.md) · [Português](docs/README.pt.md) · [Italiano](docs/README.it.md) · [한국어](docs/README.ko.md)

A gedit plugin to duplicate the current line, current selection, or selected lines. Rewritten in C for gedit 49+ which [no longer supports Python plugins](https://gedit-text-editor.org/blog/2025-04-30-no-more-pythons-in-gedit.html).

Based on [hannenz/duplicate](https://github.com/hannenz/duplicate).

## Default Shortcut

`Ctrl+Shift+D` — Duplicate line/selection

## Build

Requires `gedit-devel` and `meson`:

```bash
# Fedora
sudo dnf install gedit-devel meson

# Build
meson setup builddir
meson compile -C builddir
```

## Install

Copy the `.so` and `.plugin` files to gedit's plugin directory:

```bash
cp builddir/libduplicateline.so duplicateline.plugin ~/.local/share/gedit/plugins/
```

Then enable "Duplicate Line" in gedit → Preferences → Plugins.

## Change Shortcut

Edit `duplicateline.c`, find:

```c
const gchar *accels[] = { "<Primary><Shift>d", NULL };
```

Replace with your desired key combination, then rebuild and reinstall. Examples:
- `<Primary><Shift>d` → Ctrl+Shift+D
- `<Alt>d` → Alt+D
- `<Primary>d` → Ctrl+D

## License

GPL-2.0-or-later
