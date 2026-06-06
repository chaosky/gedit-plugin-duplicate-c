# Plugin di duplicazione riga per Gedit (C)

**Leggi in altre lingue:** [English](../README.md) · [日本語](README.ja.md) · [中文](README.zh.md) · [Русский](README.ru.md) · [Français](README.fr.md) · [Español](README.es.md) · [Português](README.pt.md) · [한국어](README.ko.md)

Un plugin per gedit per duplicare la riga corrente, la selezione corrente o le righe selezionate. Riscritto in C per gedit 49+, che [non supporta più i plugin Python](https://gedit-text-editor.org/blog/2025-04-30-no-more-pythons-in-gedit.html).

Basato su [hannenz/duplicate](https://github.com/hannenz/duplicate).

## Scorciatoia predefinita

`Ctrl+Shift+D` — Duplica riga/selezione

## Compilazione

Richiede `gedit-devel` e `meson`:

```bash
# Fedora
sudo dnf install gedit-devel meson

# Compilazione
meson setup builddir
meson compile -C builddir
```

## Installazione

Copia i file `.so` e `.plugin` nella directory dei plugin di gedit:

```bash
cp builddir/libduplicateline.so duplicateline.plugin ~/.local/share/gedit/plugins/
```

Quindi abilita «Duplicate Line» in gedit → Preferenze → Plugin.

## Modificare la scorciatoia

Modifica `duplicateline.c` e trova:

```c
const gchar *accels[] = { "<Primary><Shift>d", NULL };
```

Sostituiscila con la combinazione di tasti desiderata, poi ricompila e reinstalla. Esempi:
- `<Primary><Shift>d` → Ctrl+Shift+D
- `<Alt>d` → Alt+D
- `<Primary>d` → Ctrl+D

## Licenza

GPL-2.0-or-later
