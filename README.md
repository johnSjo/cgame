# cgame

Playing around with stuff from an old book on c game programming

Using:

- Dosbox-x
- Borland C++ 3.1 (only for compiling and build the project)
- vs code

## Dosbox-x

Set a path variable to the borland install bin directory (in my case: `c:\tools\borlandc\bin`).

Configure it however you like, but here are some recommendations:

- `aspect = true`, since 320x200 is wider than 4/3 this will stretch the image to more resemble the old crt style.
- `cycles = fixed 12000`, this was a god compromise of speed and stability on my machine.
- `cols = 80`
- `lins = 43`, to see a bit more of the compilation output

## Building project

### Prerequisite

Update the borland include/lib paths, just replace `c:\tools\borlandc` in the `makefile` and various `*.cfg` files to where you have your borland install.

### make

Run `./make` to build the whole project (game & gfx library)

**Parameters:**

target:

- `-DG` the game executable
- `-DL` the gfx library

(if you use one or more targets only they will be built, unlike if you use none -> all will be built)

extra options:

- `-DP` to compile in production mode (TODO: change the compiler settings for prod)

Executable will be placed in `./bin`

### gfxlib - Graphics Library

In the `./lib` folder lives the graphics library, i.e. various non-game related graphical helper functions.

The gfxlib in `./lib` is build together with the main make file

**TODO:** see if we can change so that the lib only rebuilds changed components (currently we have to manually set a flag to trigger a rebuild of the library)

### cgame

_wip_

## Replacing functions

The following functions from the book need to be replaced to compile with Borland

```
_int86() -> int86()
_outp() -> outportb()
_inp() -> inportb()
```

## Borland settings, if using the ide:

**note**, I only used the ide in the beginning to set up the project and then continued with the cli tools and vs code as the editor. Which means that these setting may not be all that are needed.

```
Options->Compiler->Model->Compact
        ⌙Debugger->Program Heap Size->640K (as to not run out of memory while running the app from the ide)
```
