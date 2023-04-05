.AUTODEPEND

.PATH.obj = .\bin

#		*Translator Definitions*
CC = bcc +CGAME.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = C:\TOOLS\BORLANDC\LIB;.\lib
EXE = clean_exe .\bin\cgame.exe
LIB = clean_lib lib

!if $d(G) || $d(L)
LIB =
EXE =
!endif

!if $d(G)
EXE = clean_exe .\bin\cgame.exe
!endif

!if $d(L)
LIB = clean_lib lib
!endif

!if $d(P)
FLAG = -DPROD
!else
FLAG = -DDEV
!endif

all: $(LIB) $(EXE)

#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
 cgame.obj

clean_exe:
	del /q .\bin\*.*

#		*Explicit Rules*
.\bin\cgame.exe: cgame.cfg $(EXE_dependencies)
  $(TLINK) /3/v/x/c/P-/L$(LIBPATH) @&&|
c0c.obj+
.\bin\cgame.obj
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

clean_lib:
	del /q .\lib\*.obj .\lib\*.lib

lib: vmode.obj text.obj color.obj pcx.obj sprite.obj \
assets.obj file.obj polygon.obj
	tlib lib\gfxlib +-lib\vmode.obj
	tlib lib\gfxlib +-lib\text.obj
	tlib lib\gfxlib +-lib\color.obj
	tlib lib\gfxlib +-lib\pcx.obj
	tlib lib\gfxlib +-lib\sprite.obj
	tlib lib\gfxlib +-lib\assets.obj
	tlib lib\gfxlib +-lib\file.obj
	tlib lib\gfxlib +-lib\polygon.obj
	tlib lib\gfxlib *, lib\log

vmode.obj: lib\gfxlib.cfg lib\src\vmode.c
	bcc +lib\gfxlib.cfg $(FLAG) lib\src\vmode.c

text.obj: lib\gfxlib.cfg lib\src\text.c
	bcc +lib\gfxlib.cfg $(FLAG) lib\src\text.c

color.obj: lib\gfxlib.cfg lib\src\color.c
	bcc +lib\gfxlib.cfg $(FLAG) lib\src\color.c

pcx.obj: lib\gfxlib.cfg lib\src\pcx.c
	bcc +lib\gfxlib.cfg $(FLAG) lib\src\pcx.c

sprite.obj: lib\gfxlib.cfg lib\src\sprite.c
	bcc +lib\gfxlib.cfg $(FLAG) lib\src\sprite.c

assets.obj: lib\gfxlib.cfg lib\src\assets.c
	bcc +lib\gfxlib.cfg $(FLAG) lib\src\assets.c

file.obj: lib\gfxlib.cfg lib\src\file.c
	bcc +lib\gfxlib.cfg $(FLAG) lib\src\file.c

polygon.obj: lib\gfxlib.cfg lib\src\polygon.c
	bcc +lib\gfxlib.cfg $(FLAG) lib\src\polygon.c
