# cgame

Playing around with stuff from an old book on c game programming

Using Dosbox-x and Borland C++ 2.0

## Borland settings

```
Options->Compiler->Model->Compact
        ⌙Debugger->Program Heap Size->640K (as to not run out of memory while running the app from the ide)
```

## Replacing functions

The following functions need to be replaced to compile with Borland

```
_int86() -> int86()
_outp() -> outportb()
_inp() -> inportb()
```
