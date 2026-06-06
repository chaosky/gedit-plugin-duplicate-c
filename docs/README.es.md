# Complemento de duplicación de línea para Gedit (C)

**Leer en otros idiomas:** [English](../README.md) · [日本語](README.ja.md) · [中文](README.zh.md) · [Русский](README.ru.md) · [Français](README.fr.md) · [Português](README.pt.md) · [Italiano](README.it.md) · [한국어](README.ko.md)

Un complemento de gedit para duplicar la línea actual, la selección actual o las líneas seleccionadas. Reescrito en C para gedit 49+, que [ya no admite complementos de Python](https://gedit-text-editor.org/blog/2025-04-30-no-more-pythons-in-gedit.html).

Basado en [hannenz/duplicate](https://github.com/hannenz/duplicate).

## Atajo predeterminado

`Ctrl+Shift+D` — Duplicar línea/selección

## Compilación

Requiere `gedit-devel` y `meson`:

```bash
# Fedora
sudo dnf install gedit-devel meson

# Compilación
meson setup builddir
meson compile -C builddir
```

## Instalación

Copia los archivos `.so` y `.plugin` al directorio de complementos de gedit:

```bash
cp builddir/libduplicateline.so duplicateline.plugin ~/.local/share/gedit/plugins/
```

Luego activa «Duplicate Line» en gedit → Preferencias → Complementos.

## Cambiar el atajo

Edita `duplicateline.c` y busca:

```c
const gchar *accels[] = { "<Primary><Shift>d", NULL };
```

Reemplázalo con la combinación de teclas que desees, luego recompila y reinstala. Ejemplos:
- `<Primary><Shift>d` → Ctrl+Shift+D
- `<Alt>d` → Alt+D
- `<Primary>d` → Ctrl+D

## Licencia

GPL-2.0-or-later
