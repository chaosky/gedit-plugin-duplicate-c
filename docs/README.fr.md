# Plugin de duplication de ligne pour Gedit (C)

**Lire dans d'autres langues :** [English](../README.md) · [日本語](README.ja.md) · [中文](README.zh.md) · [Русский](README.ru.md) · [Español](README.es.md) · [Português](README.pt.md) · [Italiano](README.it.md) · [한국어](README.ko.md)

Un plugin gedit pour dupliquer la ligne actuelle, la sélection actuelle ou les lignes sélectionnées. Réécrit en C pour gedit 49+ qui [ne prend plus en charge les plugins Python](https://gedit-text-editor.org/blog/2025-04-30-no-more-pythons-in-gedit.html).

Basé sur [hannenz/duplicate](https://github.com/hannenz/duplicate).

## Raccourci par défaut

`Ctrl+Shift+D` — Dupliquer la ligne/sélection

## Compilation

Nécessite `gedit-devel` et `meson` :

```bash
# Fedora
sudo dnf install gedit-devel meson

# Compilation
meson setup builddir
meson compile -C builddir
```

## Installation

Copiez les fichiers `.so` et `.plugin` dans le répertoire des plugins de gedit :

```bash
cp builddir/libduplicateline.so duplicateline.plugin ~/.local/share/gedit/plugins/
```

Activez ensuite « Duplicate Line » dans gedit → Préférences → Greffons.

## Dépannage

### `libgedit-49.so: cannot open shared object file: No such file or directory`

Si le plugin ne se charge plus après une mise à niveau de gedit et que vous voyez un message comme :

```
Failed to load module 'duplicateline': libgedit-49.so: cannot open shared object file: No such file or directory
Error loading plugin 'duplicateline'
```

c'est **attendu après une mise à niveau majeure de gedit**. Le `.so` compilé est lié au `libgedit-<N>.so` exact installé au moment de la compilation (par exemple `libgedit-49.so` pour gedit 49). Lorsque gedit est mis à niveau (par exemple vers 50), l'ancienne bibliothèque est supprimée, donc le plugin ne la trouve plus.

**Solution : recompilez simplement pour le nouveau gedit et réinstallez.**

```bash
rm -rf builddir
meson setup builddir
meson compile -C builddir
cp builddir/libduplicateline.so ~/.local/share/gedit/plugins/
```

Redémarrez ensuite gedit. Vous devez le faire une fois après chaque mise à niveau majeure de gedit.

## Modifier le raccourci

Éditez `duplicateline.c` et trouvez :

```c
const gchar *accels[] = { "<Primary><Shift>d", NULL };
```

Remplacez par la combinaison de touches souhaitée, puis recompilez et réinstallez. Exemples :
- `<Primary><Shift>d` → Ctrl+Shift+D
- `<Alt>d` → Alt+D
- `<Primary>d` → Ctrl+D

## Licence

GPL-2.0-or-later
