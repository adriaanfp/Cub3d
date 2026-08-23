*This project has been created as part of the 42 curriculum by aflores- and jugarcia.*

# Cub3D - Raycasting Game Engine

## Description
Cub3D is a 3D game engine built in C using raycasting techniques, inspired by the classic 1992 game *Wolfenstein 3D*. The primary goal of this project is to explore computer graphics fundamentals, real-time rendering, dynamic views within a maze, linear algebra, and event handling using the MiniLibX library.

### Features
- **Real-time 3D rendering** using raycasting (Digital Differential Analysis - DDA).
- **Textured walls** with direction-specific textures (North, South, East, West).
- **Smooth player movement** (WASD) and **camera rotation** (Left/Right arrow keys).
- **Custom map parsing** (`.cub` files) with validation for closed walls, colors, and valid spawn orientations.
- **Window management** with clean exit hooks (ESC key and window close button).

---

## Instructions

### Requirements
- GCC compiler (C17 standard support)
- Make build system
- X11 development libraries (Linux)
- MiniLibX graphics library

### Linux Dependencies Setup
```bash
sudo apt-get install gcc make libx11-dev libxext-dev libbsd-dev