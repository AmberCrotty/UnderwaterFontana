# Underwater Fontana #

This is an example C++ application using the SDL library.
It tries to be as nicely C++11 as possible but do keep in
mind that SDL is written in C and, at some stage, you have
to interface with it.

## Story ##
The wibble wobbles have lost their ability to swim and are falling down onto your home!
You must defend where you live at all costs, but be careful if their tentacles touch you it'll leave a sting.
**Underwater Fontana**.

## Installation ##
You will have to have the SDL development libraries installed on
your system.  The easiest way to compile is to use a command-line

```bash
$ g++ -c -std=c++11 src/*.cpp
$ g++ -o starship *.o -lSDL2 -lSDL2_image
```

which will produce an executable file called "starship" in the
top-level directory.  To execute this file do the following

`$ ./UnderwaterFontana`
 
from the top-level directory.  The game will expect to find the
`assets` directory under its current working directory.

## Credits ##
The sprites in this game were made by me.
