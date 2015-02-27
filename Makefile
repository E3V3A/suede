HOST = x86_64-w64-mingw32
CFLAGS = -s -Wall -Wextra -pedantic -std=c99 -mwindows
PROGRAM = suede
CC = $(HOST)-gcc
WINDRES = $(HOST)-windres
VR != git log --oneline | wc -l
.RECIPEPREFIX != ps

$(PROGRAM):
  $(WINDRES) $@.rc $@.coff
  $(CC) $(CFLAGS) -o $@ $@.c $@.coff

dist: $(PROGRAM)
  7za a $<-$(VR).zip $<.exe kill.bat README.md

clean:
  rm -fv *.coff *.exe *.zip *.log

.PHONY: $(PROGRAM)
