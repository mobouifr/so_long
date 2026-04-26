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
<summary>Raw keycodes (Linux MiniLibX)</summary>

```
Up: 65362  ·  Down: 65364  ·  Left: 65361  ·  Right: 65363  ·  ESC: 65307
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

```bash
git clone https://github.com/mobouifr/so_long.git
cd so_long
make
./so_long maps/map.ber
```

> Always launch from the project root — texture paths are relative (`textures/*.xpm`).

### Makefile rules

| Rule | Effect |
|---|---|
| `make` | Compile `so_long` |
| `make clean` | Remove object files |
| `make fclean` | Remove objects and binary |
| `make re` | Full rebuild |

---

## Resources

- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- `man 2 open` · `man 2 read` · `man 2 close` · `man 3 malloc` · `man 3 free`
- 42 so_long subject guidelines

### AI usage

AI assistance was used to structure and write this README based on the actual source files and project behavior. It was not used to generate code or invent features not present in the codebase.
