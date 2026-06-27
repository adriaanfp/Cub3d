# Cub3D - Raycasting Game Engine

A 3D game engine built in C using raycasting techniques, inspired by classic games like Wolfenstein 3D. This project is part of the 42 school curriculum.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Map Format](#map-format)
- [Code Architecture](#code-architecture)
- [Controls](#controls)
- [Project Structure](#project-structure)

## Overview

Cub3D is a raycasting engine that renders a 3D perspective from a 2D map. The project demonstrates fundamental computer graphics concepts including:
- Raycasting algorithm (DDA - Digital Differential Analysis)
- Texture mapping
- Player movement and collision detection
- Event handling and real-time rendering

## Features

- **Real-time 3D rendering** using raycasting
- **Textured walls** with different textures for each cardinal direction (North, South, East, West)
- **Smooth player movement** with WASD controls
- **Camera rotation** using arrow keys
- **Configurable maps** via `.cub` files
- **Collision detection** to prevent walking through walls
- **Customizable floor and ceiling colors**

## Requirements

- **GCC** compiler with C17 support
- **Make** build system
- **X11** development libraries (Linux)
- **MiniLibX** graphics library (included in `minilibx/` directory)

### Linux Dependencies

```bash
sudo apt-get install gcc make libx11-dev libxext-dev libbsd-dev
```

## Installation

1. Clone the repository:
```bash
git clone <repository-url>
cd Cub3d
```

2. Compile the project:
```bash
make
```

This will:
- Compile the MiniLibX library
- Compile all source files
- Link everything into the `cub3D` executable

## Usage

Run the program with a map file:

```bash
./cub3D maps/test.cub
```

or

```bash
./cub3D maps/maze.cub
```

## Map Format

Map files use the `.cub` extension and follow this format:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 135,206,235

11111111111
10000000001
10N00000001
10000000001
11111111111
```

### Configuration Elements

- **NO/SO/WE/EA**: Texture paths for North, South, West, East walls
- **F**: Floor color in RGB format (R,G,B)
- **C**: Ceiling color in RGB format (R,G,B)
- **Map grid**:
  - `1`: Wall
  - `0`: Empty space
  - `N/S/E/W`: Player starting position and orientation
  - ` ` (space): Empty space (must be surrounded by walls)

### Map Rules

1. Map must be surrounded by walls (`1`)
2. Only one player position allowed
3. Valid characters: `0`, `1`, `N`, `S`, `E`, `W`, and space
4. All empty spaces must be enclosed by walls

## Code Architecture

### Core Components

#### 1. **Main Loop** (`main.c`)
- Initializes MiniLibX
- Loads and validates the map
- Sets up event hooks
- Starts the rendering loop

#### 2. **Parsing System** (`parsing*.c`)
- **parsing.c**: Main parsing coordinator
- **parsing_config.c**: Parses textures and colors
- **parsing_map.c**: Reads the map grid
- **parsing_validation.c**: Validates map integrity
- **parsing_utils.c**: Helper functions for parsing

#### 3. **Raycasting Engine** (`raycasting.c`)
Implements the DDA algorithm:
```c
double cast_ray(t_data *data, int x, double *params)
```
- Calculates ray direction for each screen column
- Performs DDA to find wall intersections
- Returns perpendicular wall distance to avoid fisheye effect
- Stores hit information (side, wall_x, ray direction)

#### 4. **Rendering System** (`render.c`, `render_utils.c`)
- **render.c**: Main rendering loop
  - `render_frame()`: Called every frame
  - `render_walls()`: Iterates through screen columns
  - `draw_wall_column()`: Draws textured wall slices
  
- **render_utils.c**: Helper functions
  - `my_mlx_pixel_put()`: Fast pixel drawing
  - `get_texture_color()`: Extracts color from texture
  - `select_texture()`: Chooses correct wall texture
  - `draw_background()`: Renders floor and ceiling

#### 5. **Movement System** (`movement.c`)
- `move_forward_backward()`: Forward/backward movement with collision
- `move_strafe()`: Lateral movement (strafing)
- `rotate_camera()`: Camera rotation using rotation matrices
- `update_movement()`: Processes all active key states

#### 6. **Event Handling** (`events.c`)
- `key_press()`: Handles key press events
- `key_release()`: Handles key release events
- `close_window()`: Cleanup and exit

#### 7. **Texture Management** (`textures.c`)
- `load_textures()`: Loads XPM textures into memory
- `free_textures()`: Frees texture resources

#### 8. **Player Initialization** (`player.c`)
- Finds player position in map
- Sets initial direction and camera plane based on orientation (N/S/E/W)
- Validates single player constraint

### Key Data Structures

```c
typedef struct s_data {
    void        *mlx_ptr;       // MiniLibX instance
    void        *win_ptr;       // Window pointer
    void        *img_ptr;       // Image buffer
    char        *img_data;      // Image data pointer
    t_map       map;            // Map configuration
    t_texture   tex_no/so/we/ea; // Wall textures
    double      pos_x, pos_y;   // Player position
    double      dir_x, dir_y;   // Direction vector
    double      plane_x, plane_y; // Camera plane
    int         key_w/a/s/d;    // Movement key states
    int         key_left/right; // Rotation key states
} t_data;
```

### Raycasting Algorithm

1. **For each screen column (x)**:
   - Calculate ray direction based on camera position and plane
   - Initialize DDA variables (delta distances, step directions)
   
2. **DDA Loop**:
   - Step through map grid
   - Check for wall collision
   - Track which side was hit (vertical/horizontal)
   
3. **Calculate wall height**:
   - Use perpendicular distance to avoid fisheye
   - `line_height = WIN_HEIGHT / perp_wall_dist`
   
4. **Texture mapping**:
   - Calculate exact hit point on wall
   - Map to texture coordinates
   - Draw vertical texture slice

5. **Render**:
   - Draw ceiling (top half)
   - Draw textured wall column
   - Draw floor (bottom half)

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit program |

## Project Structure

```
Cub3d/
├── main.c              # Entry point and initialization
├── events.c            # Event handling (keyboard, window)
├── movement.c          # Player movement logic
├── render.c            # Main rendering loop
├── render_utils.c      # Rendering helper functions
├── raycasting.c        # Raycasting algorithm (DDA)
├── textures.c          # Texture loading and management
├── parsing.c           # Main parsing coordinator
├── parsing_config.c    # Parse textures and colors
├── parsing_map.c       # Parse map grid
├── parsing_validation.c # Validate map integrity
├── parsing_utils.c     # Parsing helper functions
├── player.c            # Player initialization
├── utils.c             # String utilities
├── get_next_line.c     # File reading utility
├── cub3d.h             # Header file with all declarations
├── Makefile            # Build configuration
├── minilibx/           # MiniLibX graphics library
├── maps/               # Example map files
│   ├── test.cub
│   └── maze.cub
└── textures/           # Wall texture files (XPM format)
```

## Technical Details

### Coordinate System
- **Map coordinates**: Integer grid positions
- **Player position**: Floating-point for smooth movement
- **Direction vector**: Unit vector indicating player orientation
- **Camera plane**: Perpendicular to direction, defines FOV

### Performance Optimizations
- Direct pixel buffer manipulation (no individual `mlx_pixel_put` calls)
- Pre-calculated delta distances
- Integer-based DDA stepping
- Single image buffer updated per frame

### Memory Management
- All dynamically allocated memory is properly freed
- Textures are loaded once at startup
- Map grid is freed on exit
- MiniLibX resources are cleaned up properly

## Compilation Flags

```makefile
CFLAGS = -Wall -Wextra -Werror -std=gnu17
```

- `-Wall -Wextra -Werror`: Strict error checking
- `-std=gnu17`: C17 standard with GNU extensions

## Makefile Targets

- `make` or `make all`: Compile the project
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Recompile from scratch

## Error Handling

The program validates:
- File extension (`.cub`)
- File accessibility
- Texture file paths
- Color values (0-255 RGB)
- Map format and characters
- Map closure (walls surrounding playable area)
- Single player position
- Valid player orientation

## Credits

- **42 School** for the project specifications
- **MiniLibX** graphics library
- Raycasting technique inspired by **Lode Vandevenne's** tutorials

## License

This project is part of the 42 school curriculum and follows their academic policies.
