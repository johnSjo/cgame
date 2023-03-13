# cgame

Playing around with stuff from an old book on c game programming

Using Dosbox-x and Borland C++ 2.0

## Replacing functions

The following functions need to be replaced to compile with Borland

```
_int86() -> int86()
_outp() -> outportb()
_inp() -> inportb()
```
