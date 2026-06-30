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

## Solución de problemas

### `libgedit-49.so: cannot open shared object file: No such file or directory`

Si el complemento deja de cargarse tras actualizar gedit y ves algo como:

```
Failed to load module 'duplicateline': libgedit-49.so: cannot open shared object file: No such file or directory
Error loading plugin 'duplicateline'
```

esto es **esperable tras una actualización de versión mayor de gedit**. El `.so` compilado está enlazado con el `libgedit-<N>.so` exacto que estaba instalado al compilarlo (por ejemplo, `libgedit-49.so` para gedit 49). Cuando se actualiza gedit (por ejemplo, a 50), la biblioteca antigua se elimina, por lo que el complemento ya no puede encontrarla.

**Solución: simplemente recompila para el nuevo gedit y reinstala.**

```bash
rm -rf builddir
meson setup builddir
meson compile -C builddir
cp builddir/libduplicateline.so ~/.local/share/gedit/plugins/
```

Luego reinicia gedit. Debes hacer esto una vez después de cada actualización de versión mayor de gedit.

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
