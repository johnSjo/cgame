.AUTODEPEND

.PATH.obj = .\BIN

#		*Translator Definitions*
CC = bcc +CGAME.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = C:\TOOLS\BORLANDC\LIB;.\LIB\bin
INCLUDEPATH = C:\TOOLS\BORLANDC\INCLUDE;.\LIB

!if $d(run)
all: start .\bin\cgame.exe run
!else
all: start .\bin\cgame.exe
!endif

start:
	mkdir bin
	mkdir .\lib\bin

#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
 lib\bin\gfxlib.lib \
 cgame.obj

#		*Explicit Rules*
.\bin\cgame.exe: cgame.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/L$(LIBPATH) @&&|
c0c.obj+
.\bin\\cgame.obj
.\bin\cgame
		# no map file
lib\bin\gfxlib.lib+
graphics.lib+
emu.lib+
mathc.lib+
cc.lib
|

#		*Individual File Dependencies*
cgame.obj: cgame.cfg src\cgame.c 
	$(CC) -c src\cgame.c


lib\bin\gfxlib.lib: vmode.obj text.obj
	tlib lib\bin\gfxlib +-lib\bin\vmode.obj
	tlib lib\bin\gfxlib +-lib\bin\text.obj
	tlib lib\bin\gfxlib *, lib\log

vmode.obj: lib\gfxlib.cfg lib\src\vmode.c
	bcc +lib\gfxlib.cfg lib\src\vmode.c

text.obj: lib\gfxlib.cfg lib\src\text.c
	bcc +lib\gfxlib.cfg lib\src\text.c


run:
	.\bin\cgame.exe

.PRECIOUS:run