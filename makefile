.AUTODEPEND

.PATH.obj = .\BIN

#		*Translator Definitions*
CC = bcc +CGAME.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = C:\TOOLS\BORLANDC\LIB;.\LIB
INCLUDEPATH = C:\TOOLS\BORLANDC\INCLUDE;.\LIB

!if $d(run)
all: start .\bin\cgame.exe run
!else
all: start .\bin\cgame.exe
!endif

start:
	@echo -- Create bin folder --
	mkdir bin
	@echo -- Deleting old files --
	del .\bin\cgame.exe
	del .\bin\cgame.obj
	@echo -- done --

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
.\bin\cgame.exe: cgame.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/L$(LIBPATH) @&&|
c0c.obj+
.\bin\\cgame.obj
.\bin\cgame
		# no map file
lib\gfxlib.lib+
graphics.lib+
emu.lib+
mathc.lib+
cc.lib
|


#		*Individual File Dependencies*
cgame.obj: cgame.cfg src\cgame.c 
	$(CC) -c src\cgame.c

#		*Compiler Configuration File*
# cgame.cfg: cgame.mak
#   copy &&|
# -mc
# -2
# -v
# -vi-
# -weas
# -wpre
# -n.\BIN
# -I$(INCLUDEPATH)
# -L$(LIBPATH)
# -P-.C
# | cgame.cfg

run:
	.\bin\cgame.exe

.PRECIOUS:run