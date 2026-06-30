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

## Solução de problemas

### `libgedit-49.so: cannot open shared object file: No such file or directory`

Se o plugin parar de carregar após uma atualização do gedit e você vir algo como:

```
Failed to load module 'duplicateline': libgedit-49.so: cannot open shared object file: No such file or directory
Error loading plugin 'duplicateline'
```

isso é **esperado após uma atualização de versão principal do gedit**. O `.so` compilado está vinculado ao `libgedit-<N>.so` exato que estava instalado quando você o compilou (por exemplo, `libgedit-49.so` para o gedit 49). Quando o gedit é atualizado (por exemplo, para 50), a biblioteca antiga é removida, então o plugin não consegue mais encontrá-la.

**Correção: basta recompilar para o novo gedit e reinstalar.**

```bash
rm -rf builddir
meson setup builddir
meson compile -C builddir
cp builddir/libduplicateline.so ~/.local/share/gedit/plugins/
```

Em seguida, reinicie o gedit. Você precisa fazer isso uma vez após cada atualização de versão principal do gedit.

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
