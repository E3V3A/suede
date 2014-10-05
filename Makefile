HOST = x86_64-w64-mingw32
VR != git log --oneline | wc -l
.RECIPEPREFIX != ps

all:
  $(HOST)-windres suede.rc suede.o
  $(HOST)-gcc -s -Wall -Wextra -pedantic -std=c99 \
    -mwindows -osuede suede.c suede.o

dist: all
  zip -9r suede-$(VR).zip suede.exe README.md

clean:
  rm -fv *.o *.exe *.zip *.log
