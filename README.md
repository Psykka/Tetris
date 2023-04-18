# Tetris

Simple tetris game written in C++ using SDL2.

## Build
Requires:
 - Python and pip for installing the building tools
 - Any C compiler (gcc, clang, etc.)

Install meson and ninja build system:
```
$ pip install meson ninja
```

Build project:
```
# create build folder for meson
$ meson builddir

# compile project
$ meson compile -C build
```

## Run
```
$ ./build/tetris
```

## Controls
- `Left` and `Right` arrow keys to move the piece.
- `X` to rotate the piece clockwise.
- `Z` to rotate the piece counter-clockwise.
- `Down` arrow key to move the piece faster.
- `Space` to drop the piece.
- `Esc` to quit the game.
