# Плагин дублирования строк для Gedit (C)

**На других языках:** [English](../README.md) · [日本語](README.ja.md) · [中文](README.zh.md) · [Français](README.fr.md) · [Español](README.es.md) · [Português](README.pt.md) · [Italiano](README.it.md) · [한국어](README.ko.md)

Плагин для gedit, который дублирует текущую строку, текущее выделение или выделенные строки. Переписан на C для gedit 49+, который [больше не поддерживает плагины на Python](https://gedit-text-editor.org/blog/2025-04-30-no-more-pythons-in-gedit.html).

Основан на [hannenz/duplicate](https://github.com/hannenz/duplicate).

## Сочетание клавиш по умолчанию

`Ctrl+Shift+D` — Дублировать строку/выделение

## Сборка

Требуются `gedit-devel` и `meson`:

```bash
# Fedora
sudo dnf install gedit-devel meson

# Сборка
meson setup builddir
meson compile -C builddir
```

## Установка

Скопируйте файлы `.so` и `.plugin` в каталог плагинов gedit:

```bash
cp builddir/libduplicateline.so duplicateline.plugin ~/.local/share/gedit/plugins/
```

Затем включите «Duplicate Line» в gedit → Параметры → Модули.

## Устранение неполадок

### `libgedit-49.so: cannot open shared object file: No such file or directory`

Если после обновления gedit плагин перестал загружаться и вы видите примерно следующее:

```
Failed to load module 'duplicateline': libgedit-49.so: cannot open shared object file: No such file or directory
Error loading plugin 'duplicateline'
```

это **ожидаемо после обновления мажорной версии gedit**. Скомпилированный `.so` слинкован с тем конкретным `libgedit-<N>.so`, который был установлен на момент сборки (например, `libgedit-49.so` для gedit 49). При обновлении gedit (например, до 50) старая библиотека удаляется, и плагин больше не может её найти.

**Решение: просто пересоберите под новый gedit и переустановите.**

```bash
rm -rf builddir
meson setup builddir
meson compile -C builddir
cp builddir/libduplicateline.so ~/.local/share/gedit/plugins/
```

Затем перезапустите gedit. Это нужно делать один раз после каждого обновления мажорной версии gedit.

## Изменение сочетания клавиш

Откройте `duplicateline.c` и найдите:

```c
const gchar *accels[] = { "<Primary><Shift>d", NULL };
```

Замените на нужную комбинацию клавиш, затем пересоберите и переустановите. Примеры:
- `<Primary><Shift>d` → Ctrl+Shift+D
- `<Alt>d` → Alt+D
- `<Primary>d` → Ctrl+D

## Лицензия

GPL-2.0-or-later
