*This project has been created as part of the 42 curriculum by rzaatreh.*

# SO_LONG

## Description
**so_long** is a small 2D game project from the 42 curriculum, built using the **MiniLibX** graphics library.
The goal is to create a simple top-down game where the player collects all collectibles on the map and then exits, following strict validation rules.

The game reads a map from a `.ber` file and renders it in a window.
The player can move using the keyboard, collect items, and exit the level once all collectibles are gathered.

This project focuses on:
- Parsing and validating structured input files
- Event handling and basic graphics rendering
- Memory management and leak prevention
- Working with MiniLibX
- Implementing game logic under strict constraints

---

## Game Rules

- The map must be rectangular and surrounded by walls
- The map must contain:
    - Exactly one player (`P`)
    - Exactly one exit (`E`)
    - At least one collectible (`C`)
- The player:
    - Cannot move through walls
    - Must collect all collectibles before exiting
- Each valid move is counted and printed to standard output
- The game exits cleanly when the player reaches the exit or presses `ESC`

---

## Map Elements

| Character | Description |
|---------|------------|
| `1` | Wall |
| `0` | Floor |
| `P` | Player |
| `C` | Collectible |
| `E` | Exit |

---

## Controls

| Key | Action |
|----|--------|
| `W` / `↑` | Move up |
| `S` / `↓` | Move down |
| `A` / `←` | Move left |
| `D` / `→` | Move right |
| `ESC` | Exit the game |

---

## Instructions

### Prerequisites
- Unix-based operating system (Linux or macOS)
- `cc`
- `make`
- MiniLibX (Provided by 42)


### Compilation

Clone the repository and compile the project using:

```bash
make
```
Run the game by providing a valid `.ber` map file:
```
./so_long maps/valid.ber
```
This will output the game window.

## Textures
All textures are provided in XPM format and are loaded at runtime using MiniLibX.

Each tile is rendered on top of a floor texture to ensure proper layering.

## Resources



### AI Usage

---
AI tools were used as a learning and assistance resource, not as a code generator.

They were used to:
- Clarify project requirements and constraints.
- Understand MiniLibX behavior and memory management
- Improve code structure and readability
