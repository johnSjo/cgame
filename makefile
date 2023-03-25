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
RUN = run
!endif

!if $d(lib)
LIB = lib
!endif

!if $d(PROD)
FLAG = -DPROD
!else
FLAG = -DDEV
!endif

all: start $(LIB) .\bin\cgame.exe $(RUN)

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
 cgame.obj

#		*Explicit Rules*
.\bin\cgame.exe: cgame.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/L$(LIBPATH) @&&|
c0c.obj+
.\bin\\cgame.obj
.\bin\cgame
		# no map file
gfxlib.lib+
graphics.lib+
emu.lib+
mathc.lib+
cc.lib
|

#		*Individual File Dependencies*
cgame.obj: cgame.cfg src\cgame.c 
	$(CC) -c $(FLAG) src\cgame.c


lib: vmode.obj text.obj color.obj
	tlib lib\bin\gfxlib +-lib\bin\vmode.obj
	tlib lib\bin\gfxlib +-lib\bin\text.obj
	tlib lib\bin\gfxlib +-lib\bin\color.obj
	tlib lib\bin\gfxlib *, lib\log

vmode.obj: lib\gfxlib.cfg lib\src\vmode.c
	bcc +lib\gfxlib.cfg lib\src\vmode.c

text.obj: lib\gfxlib.cfg lib\src\text.c
	bcc +lib\gfxlib.cfg lib\src\text.c

color.obj: lib\gfxlib.cfg lib\src\color.c
	bcc +lib\gfxlib.cfg lib\src\color.c


run:
	.\bin\cgame.exe

.PRECIOUS:run