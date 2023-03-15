# cgame

Playing around with stuff from an old book on c game programming

Using:

- Dosbox-x
- Borland C++ 3.1 (only for compiling and build the project)
- vs code

## Building project

### gfxlib

In `./lib` there's a `makelib.bat` file to compile and build the lib file

TODO: convert to a make file

### cgame

A `./bin` folder is needed

Run `./make -f cgame.mak` to build the project

## Borland settings

Path used: `c:\tools\borlandc\` (don't forget to set path variable in doxbox)

### If using the ide:

```
Options->Compiler->Model->Compact
        ⌙Debugger->Program Heap Size->640K (as to not run out of memory while running the app from the ide)
```

## Replacing functions

The following functions from the book need to be replaced to compile with Borland

```
_int86() -> int86()
_outp() -> outportb()
_inp() -> inportb()
```
