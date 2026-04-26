*This project has been created as part of the 42 curriculum by mobouifr.*

<div align="center">

# so_long

**A tiny 2D tile game built in C with MiniLibX.**

*Collect everything. Find the exit. Count your steps.*

[![Language](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics](https://img.shields.io/badge/MiniLibX-FF6B35?style=for-the-badge)](https://harm-smits.github.io/42docs/libs/minilibx)
[![42](https://img.shields.io/badge/42-1337-000000?style=for-the-badge)](https://42.fr)

</div>

---

<div align="center">
  <img src="screenshots/so_long.png" alt="so_long gameplay" width="80%"/>
</div>

---

## What is this?

`so_long` is one of the first graphical projects in the 42 core curriculum. The concept is minimal on purpose — read a map from a `.ber` file, validate every rule, render it tile by tile, and let the player navigate to victory.

What's actually interesting is what's hiding under that simplicity. You parse a custom file format, validate its structure and playability, manage dynamic memory for the map grid, wire up keyboard hooks, run a render loop, and enforce game logic — all in C, all from scratch.

> No game framework. No physics engine. Just C, file descriptors, and MLX pixels.

---

## Gameplay

<div align="center">

| Symbol | Meaning |
|:---:|---|
| `1` | Wall — impassable |
| `0` | Floor — walkable |
| `P` | Player spawn — exactly one |
| `C` | Collectible — at least one |
| `E` | Exit — exactly one |

</div>

Collect every **C**, then step onto **E**. The player cannot walk through walls. Every valid move prints the current step count to the terminal.

---

## Features

| Feature | | Notes |
|---|:---:|---|
| `.ber` map loading | ✓ | Line-by-line via `get_next_line` |
| Rectangular map check | ✓ | Every row must have equal width |
| Character validation | ✓ | Only `1` `0` `P` `C` `E` accepted |
| Required entity counts | ✓ | Exactly 1 `P`, exactly 1 `E`, at least 1 `C` |
| Border wall validation | ✓ | Outer frame must be walls |
| Playability check | ✓ | Flood fill verifies full reachability |
| Tile rendering with XPM | ✓ | Wall, floor, player, collectible, exit |
| Floor-first compositing | ✓ | Ensures consistent overlay on macOS and Linux |
| Movement + collision | ✓ | Arrow keys — target tile must be valid |
| Win condition | ✓ | Exit only triggers after all collectibles |
| ESC / window-close | ✓ | Both paths call clean shutdown |

---

## Controls

<div align="center">

| Key | Action |
|:---:|---|
| `↑` | Move up |
| `↓` | Move down |
| `←` | Move left |
| `→` | Move right |
| `ESC` | Quit |

</div>

<details>
<summary>Raw keycodes (macOS MiniLibX)</summary>

```
Up: 126  ·  Down: 125  ·  Left: 123  ·  Right: 124  ·  ESC: 53
```

</details>

---

## Map format

A valid `.ber` map:

```
11111111111
10P00CC00E1
11111111111
```

**Rules at a glance:**

```
✓  Extension must be .ber
✓  Every row same width (rectangular)
✓  Fully enclosed by walls
✓  Exactly one P  ·  exactly one E  ·  at least one C
✗  Any other character → Error
```

---

## Project structure

```
so_long/
│
├── Makefile
├── so_long.h                    ← structs, prototypes, includes
├── so_long.c                    ← entry point and game loop
│
├── so_long_utils_00.c           ← map loading and memory
├── so_long_utils_01.c           ← validation helpers
├── so_long_utils_02.c           ← rendering and tile drawing
├── so_long_utils_03.c           ← movement and collision
├── so_long_mvp_utils.c          ← flood fill / playability
├── ft_putnbr_nl.c               ← move counter output
│
├── get_next_line/               ← line reader for the parser
├── maps/                        ← .ber level files
├── textures/                    ← XPM sprite assets
│
├── minilibx-linux/              ← MiniLibX Linux (X11)
├── minilibx_macos_opengl/       ← MiniLibX macOS OpenGL
└── minilibx_macos_metal/        ← MiniLibX macOS Metal (Apple Silicon)
```

---

## Getting started

### macOS

```bash
make
./so_long maps/map.ber
```

### Linux

```bash
# Install X11 dependencies
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Build MiniLibX
cd minilibx-linux && sh ./configure && cd ..

# Compile
cc -Wall -Wextra -Werror -Iminilibx-linux         \
  so_long.c so_long_utils_00.c so_long_utils_01.c \
  so_long_utils_02.c so_long_utils_03.c           \
  so_long_mvp_utils.c ft_putnbr_nl.c              \
  get_next_line/get_next_line.c                    \
  get_next_line/get_next_line_utils.c              \
  -Lminilibx-linux -lmlx -L/usr/lib               \
  -lXext -lX11 -lm -lbsd -o so_long

./so_long maps/map.ber
```

<details>
<summary>Notes on platform compatibility</summary>

- The top-level `Makefile` currently links with `-framework OpenGL -framework AppKit` (macOS only). The Linux compile above is the manual equivalent until the Makefile is unified.
- Always launch from the project root — texture paths are relative (`textures/*.xpm`).
- Tile rendering composites the floor image first in memory before overlaying sprites, avoiding XPM transparency inconsistencies between macOS and Linux MiniLibX builds.

</details>

---

## Resources

- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- `man 2 open` · `man 2 read` · `man 2 close` · `man 3 malloc` · `man 3 free`
- 42 so_long subject guidelines
