# Gedit 行複製プラグイン (C)

**他の言語で読む:** [English](../README.md) · [中文](README.zh.md) · [Русский](README.ru.md) · [Français](README.fr.md) · [Español](README.es.md) · [Português](README.pt.md) · [Italiano](README.it.md) · [한국어](README.ko.md)

現在の行、選択範囲、または選択した複数行を複製する gedit プラグインです。Python プラグインに[対応しなくなった](https://gedit-text-editor.org/blog/2025-04-30-no-more-pythons-in-gedit.html) gedit 49+ 向けに C で書き直されました。

[hannenz/duplicate](https://github.com/hannenz/duplicate) をベースにしています。

## デフォルトのショートカット

`Ctrl+Shift+D` — 行/選択範囲を複製

## ビルド

`gedit-devel` と `meson` が必要です:

```bash
# Fedora
sudo dnf install gedit-devel meson

# ビルド
meson setup builddir
meson compile -C builddir
```

## インストール

`.so` と `.plugin` ファイルを gedit のプラグインディレクトリにコピーします:

```bash
cp builddir/libduplicateline.so duplicateline.plugin ~/.local/share/gedit/plugins/
```

その後、gedit → 設定 → プラグインで「Duplicate Line」を有効にします。

## トラブルシューティング

### `libgedit-49.so: cannot open shared object file: No such file or directory`

gedit のアップグレード後にプラグインが読み込まれなくなり、次のようなメッセージが表示される場合:

```
Failed to load module 'duplicateline': libgedit-49.so: cannot open shared object file: No such file or directory
Error loading plugin 'duplicateline'
```

これは **gedit のメジャーバージョンアップグレード後に想定される動作**です。コンパイルされた `.so` は、ビルド時にインストールされていた特定の `libgedit-<N>.so`（例: gedit 49 なら `libgedit-49.so`）にリンクされています。gedit がアップグレードされる（例: 50 へ）と古いライブラリが削除されるため、プラグインがそれを見つけられなくなります。

**対処法: 新しい gedit に対して再ビルドして再インストールするだけです。**

```bash
rm -rf builddir
meson setup builddir
meson compile -C builddir
cp builddir/libduplicateline.so ~/.local/share/gedit/plugins/
```

その後 gedit を再起動します。gedit のメジャーバージョンアップグレードのたびに一度行う必要があります。

## ショートカットの変更

`duplicateline.c` を編集し、次の行を見つけます:

```c
const gchar *accels[] = { "<Primary><Shift>d", NULL };
```

希望するキーの組み合わせに置き換えてから、再ビルドして再インストールします。例:
- `<Primary><Shift>d` → Ctrl+Shift+D
- `<Alt>d` → Alt+D
- `<Primary>d` → Ctrl+D

## ライセンス

GPL-2.0-or-later
