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

## Risoluzione dei problemi

### `libgedit-49.so: cannot open shared object file: No such file or directory`

Se il plugin smette di caricarsi dopo un aggiornamento di gedit e vedi qualcosa come:

```
Failed to load module 'duplicateline': libgedit-49.so: cannot open shared object file: No such file or directory
Error loading plugin 'duplicateline'
```

questo è **previsto dopo un aggiornamento di versione maggiore di gedit**. Il `.so` compilato è collegato all'esatto `libgedit-<N>.so` installato al momento della compilazione (ad esempio `libgedit-49.so` per gedit 49). Quando gedit viene aggiornato (ad esempio alla 50), la vecchia libreria viene rimossa, quindi il plugin non riesce più a trovarla.

**Soluzione: basta ricompilare per il nuovo gedit e reinstallare.**

```bash
rm -rf builddir
meson setup builddir
meson compile -C builddir
cp builddir/libduplicateline.so ~/.local/share/gedit/plugins/
```

Quindi riavvia gedit. Devi farlo una volta dopo ogni aggiornamento di versione maggiore di gedit.

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
