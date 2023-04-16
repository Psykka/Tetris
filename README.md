# Tetris

Simple tetris game written in C++ using SDL2.

## Build
To build the game you need C/C++ compiler and XMake. To install XMake run:

```bash
# with curl
curl -fsSL https://xmake.io/shget.text | bash

# with wget
wget https://xmake.io/shget.text -O - | bash
```

Then run:

```bash
# to build
xmake build
```

## Run
To run the game run:

```bash
# to run
xmake run
```

## Controls
- `Left` and `Right` arrow keys to move the piece.
- `Up` arrow key to rotate the piece.
- `Down` arrow key to move the piece faster.
- `Space` to drop the piece.
- `Esc` to quit the game.
