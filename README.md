# Arcade Machine — Custom Pong

A 2D OpenGL arcade game built in C++ featuring a **custom spaceship editor** and a fully playable **Pong** game. Designed as a university graphics programming assignment

---

## Overview

The project is split into two phases:

1. **Editor** — Design your own spaceship paddle by drag-and-dropping colored blocks onto a 5×13 grid.
2. **Game** — Use the designed spaceship as a paddle in a Pong match against another player.

---

## Framework

This project is built on top of a **university-provided OpenGL framework** (GLFW + GLM + OpenGL 3.3). The framework exposes a base scene class with lifecycle callbacks such as `Init()`, `Update()`, `FrameStart()`, `FrameEnd()`, `OnInputUpdate()`, `OnMouseMove()`, `OnMouseBtnPress()`, `OnMouseBtnRelease()`, and `OnWindowResize()`.

All game logic, rendering, editor functionality, physics, collision detection, and UI were implemented from scratch by me.. The framework itself was provided by the university.

---

## Features

### Editor
- Drag & drop colored blocks (grey, yellow, orange, purple) onto a grid
- Right-click to remove placed blocks
- BFS connectivity check to ensure the ship is always a connected component
- Valid-form check to ensure blocks form a rectangular shape
- Visual counter showing remaining blocks (max 10)
- **Start button** turns green when the ship is valid, red otherwise
- The designed ship is copied directly into the game as both paddles

### Pong Game
- **Two-player local multiplayer**
  - Player 1: `W` / `S`
  - Player 2: `↑` / `↓`
- Angle-based ball deflection off paddles
- Ball speed increases on every paddle hit
- Paddle hit animation (scale pulse for 1 second)
- Score tracking — first to **5 points** wins
- Win screen displayed for LEFT WIN or RIGHT WIN
- Custom digit and letter rendering (drawn with primitive lines, no fonts)

### Advanced Features
- **Multi-ball mode**: Press `1` for single ball, `2` for two simultaneous balls
- **Speed escalation**: Ball gets faster with every bounce
- **Paddle animation**: Scale animation triggers on collision

---

## Controls

| Action | Key |
|---|---|
| Move left paddle up | `W` |
| Move left paddle down | `S` |
| Move right paddle up | `↑` |
| Move right paddle down | `↓` |
| Start with 1 ball | `1` |
| Start with 2 balls | `2` |
| Place block (editor) | Left click + drag |
| Remove block (editor) | Right click |
| Start game (editor) | Right click on green start button |

---

## Project Structure

```
Tema1/
├── Tema1.cpp        # Core game logic — editor, pong, rendering, input handling
├── Tema1.h          # Class declaration, all member variables and method signatures
├── main.cpp         # Engine initialization and window setup
├── object2D.cpp     # 2D mesh creation (square, circle, custom form)
├── object2D.h       # object2D namespace declaration
├── transform2D.h    # 2D transformation matrices (translate, scale, rotate)
└── lab_list.h       # Framework include list (university-provided)
```

---

## Build & Run

This project runs within the university-provided OpenGL framework.

1. Place the `Tema1/` folder inside `src/lab_m1/`
2. Add `#include "lab_m1/Tema1/Tema1.h"` to `lab_list.h`
3. Build with Visual Studio (or CMake on Linux/macOS)
4. Run the resulting executable

> Requires: OpenGL 3.3+, GLFW, GLM

---

## Implementation Notes

- All shapes are drawn using primitive 2D meshes with `glm::mat3` transformations
- Collision detection uses AABB for paddles and circle math for the ball
- Connectivity validation uses BFS on the block grid graph
- No external font libraries — all text is hand-drawn using line segments
# Arcade-Machine-Pong-OpenGL-C-
