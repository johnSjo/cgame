.AUTODEPEND

.PATH.obj = .\BIN\

#		*Translator Definitions*
CC = bcc +CGAME.CFG
TASM = TASM
TLINK = tlink


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
  lib\gfxlib.lib \
  cgame.obj

#		*Explicit Rules*
.\bin\\cgame.exe: cgame.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/LC:\TOOLS\BORLANDC\LIB; .\LIB\ @&&|
c0c.obj+
.\bin\\cgame.obj
.\bin\\cgame
		# no map file
lib\gfxlib.lib+
emu.lib+
mathc.lib+
cc.lib+
graphics.lib
|


#		*Individual File Dependencies*
cgame.obj: src\cgame.c 
	$(CC) -c src\cgame.c

#		*Compiler Configuration File*
cgame.cfg: cgame.mak
  copy &&|
-mc
-2
-v
-n.\BIN\
-IC:\TOOLS\BORLANDC\INCLUDE; .\LIB\
-LC:\TOOLS\BORLANDC\LIB; .\LIB\
-P-.C
| cgame.cfg


