# Gedit 줄 복제 플러그인 (C)

**다른 언어로 읽기:** [English](../README.md) · [日本語](README.ja.md) · [中文](README.zh.md) · [Русский](README.ru.md) · [Français](README.fr.md) · [Español](README.es.md) · [Português](README.pt.md) · [Italiano](README.it.md)

현재 줄, 현재 선택 영역 또는 선택한 여러 줄을 복제하는 gedit 플러그인입니다. [Python 플러그인을 더 이상 지원하지 않는](https://gedit-text-editor.org/blog/2025-04-30-no-more-pythons-in-gedit.html) gedit 49+ 용으로 C로 다시 작성되었습니다.

[hannenz/duplicate](https://github.com/hannenz/duplicate)를 기반으로 합니다.

## 기본 단축키

`Ctrl+Shift+D` — 줄/선택 영역 복제

## 빌드

`gedit-devel`과 `meson`이 필요합니다:

```bash
# Fedora
sudo dnf install gedit-devel meson

# 빌드
meson setup builddir
meson compile -C builddir
```

## 설치

`.so`와 `.plugin` 파일을 gedit의 플러그인 디렉터리에 복사합니다:

```bash
cp builddir/libduplicateline.so duplicateline.plugin ~/.local/share/gedit/plugins/
```

그런 다음 gedit → 기본 설정 → 플러그인에서 "Duplicate Line"을 활성화합니다.

## 단축키 변경

`duplicateline.c`를 편집하여 다음을 찾습니다:

```c
const gchar *accels[] = { "<Primary><Shift>d", NULL };
```

원하는 키 조합으로 바꾼 다음 다시 빌드하고 설치합니다. 예:
- `<Primary><Shift>d` → Ctrl+Shift+D
- `<Alt>d` → Alt+D
- `<Primary>d` → Ctrl+D

## 라이선스

GPL-2.0-or-later
