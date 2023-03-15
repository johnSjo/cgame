@REM Remove old obj files
@DEL bin\*.OBJ

@Rem Compiling all modules
bcc -c -mc -2 -n.\BIN\ -Ic:\tools\borlandc\include -Lc:\tools\borlandc\lib src\vmode.c
bcc -c -mc -2 -n.\BIN\ -Ic:\tools\borlandc\include -Lc:\tools\borlandc\lib src\text.c

@REM Remove old libaray
@DEL gfxlib.lib

@Rem Building lib file
tlib gfxlib +bin\vmode.obj
tlib gfxlib +bin\text.obj
tlib gfxlib *, log
