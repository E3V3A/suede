#!/bin/sh
vr=$(git log --oneline | wc -l)
x86_64-w64-mingw32-windres -O coff suede.rc suede.res
x86_64-w64-mingw32-gcc -Wall -Wextra -pedantic -std=c99 \
  -mwindows -osuede suede.c suede.res
zip -9r suede-$vr.zip suede.exe README.md
