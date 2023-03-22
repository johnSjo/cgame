# cgame

Playing around with stuff from an old book on c game programming

Using:

- Dosbox-x
- Borland C++ 3.1 (only for compiling and build the project)
- vs code

## Building project

### gfxlib

The gfxlib in `./lib` is build together with the main make file

TODO: see if we can change so that the lib only rebuilds changed components (currently the whole lib is rebuilt every time)

### cgame

Run `./make` to build the project
Run `./make -Drun` to build and run the project

A `./bin` folder will be created and the exe will be placed there

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
