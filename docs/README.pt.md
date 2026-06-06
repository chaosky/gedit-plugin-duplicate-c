# Plugin de duplicação de linha para o Gedit (C)

**Ler em outros idiomas:** [English](../README.md) · [日本語](README.ja.md) · [中文](README.zh.md) · [Русский](README.ru.md) · [Français](README.fr.md) · [Español](README.es.md) · [Italiano](README.it.md) · [한국어](README.ko.md)

Um plugin do gedit para duplicar a linha atual, a seleção atual ou as linhas selecionadas. Reescrito em C para o gedit 49+, que [não oferece mais suporte a plugins em Python](https://gedit-text-editor.org/blog/2025-04-30-no-more-pythons-in-gedit.html).

Baseado em [hannenz/duplicate](https://github.com/hannenz/duplicate).

## Atalho padrão

`Ctrl+Shift+D` — Duplicar linha/seleção

## Compilação

Requer `gedit-devel` e `meson`:

```bash
# Fedora
sudo dnf install gedit-devel meson

# Compilação
meson setup builddir
meson compile -C builddir
```

## Instalação

Copie os arquivos `.so` e `.plugin` para o diretório de plugins do gedit:

```bash
cp builddir/libduplicateline.so duplicateline.plugin ~/.local/share/gedit/plugins/
```

Em seguida, ative «Duplicate Line» em gedit → Preferências → Plugins.

## Alterar o atalho

Edite `duplicateline.c` e encontre:

```c
const gchar *accels[] = { "<Primary><Shift>d", NULL };
```

Substitua pela combinação de teclas desejada, depois recompile e reinstale. Exemplos:
- `<Primary><Shift>d` → Ctrl+Shift+D
- `<Alt>d` → Alt+D
- `<Primary>d` → Ctrl+D

## Licença

GPL-2.0-or-later
