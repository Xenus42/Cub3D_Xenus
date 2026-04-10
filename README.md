# Cub3D

*This project has been created as part of the 42 curriculum by kporceil, lebroue.*

## Description

**Cub3D** is a 42 School project that implements a 3D raycasting engine in C, inspired by classic games like **Doom** and **Wolfenstein 3D**. The project demonstrates fundamental computer graphics concepts by rendering a 3D perspective view from a 2D map using raycasting and texture mapping.

### Key Features
- **Raycasting Engine**: Converts a 2D map into a 3D first-person view
- **Texture Mapping**: Applies textures to walls based on direction (North, South, East, West)
- **DDA Algorithm**: Efficient grid traversal to detect wall collisions
- **Player Movement**: 4-directional movement (forward, backward, strafe left/right)
- **Collision Detection**: Prevents walking through walls
- **Bonus Features**: Minimap (when compiled with `make bonus`)

### Project Goal
To understand and implement the core rendering technique used in early 3D games, implementing a complete raycasting pipeline: parsing configuration files, managing textures, calculating ray-wall intersections, and rendering columns based on distance.

## Instructions

### Prerequisites
- **System**: Linux
- **Compiler**: GCC with `-Wall -Wextra -Werror`
- **Libraries**: 
  - X11 (libxext-dev, libx11-dev)
  - Standard C library (libm)
- **Makefile**: Supports standard `make` targets

### Compilation

```bash
make              # Compile mandatory part
make clean        # Remove object files
make fclean       # Remove object files and executable
make re           # Recompile from scratch
```

The executable is named `cub3D`.

### Execution

```bash
./cub3D <path_to_map_file>
```

Example:
```bash
./cub3D maps/good/good_map.cub
```

### Controls

| Key | Action |
|-----|--------|
| **W** / **Up Arrow** | Move forward |
| **S** / **Down Arrow** | Move backward |
| **A** | Strafe left |
| **D** | Strafe right |
| **Left Arrow** | Rotate left |
| **Right Arrow** | Rotate right |
| **ESC** | Exit game |

## Technical Concepts

### 1. Parsing the Configuration File (.cub)

The parsing phase loads and validates the game configuration from a `.cub` file through a robust three-phase process:

**Phase 1: Line Parsing and Metadata Extraction**

- **Textures (NO/SO/WE/EA)**: Wall texture paths for each cardinal direction
  - `NO ./path/to/north.xpm` - North wall texture
  - `SO ./path/to/south.xpm` - South wall texture  
  - `WE ./path/to/west.xpm` - West wall texture
  - `EA ./path/to/east.xpm` - East wall texture
  - Each direction must have exactly one texture defined
  
- **Colors (F/C)**: Floor and ceiling RGB colors
  - `F 220,100,0` - Floor color (RGB values 0-255)
  - `C 25,25,25` - Ceiling color (RGB values 0-255)
  - Validation ensures each component is a valid integer between 0-255
  - Each color (floor and ceiling) must be defined exactly once

**Phase 2: Map Data Accumulation**

- All lines not matching texture or color patterns are accumulated as map data
- Individual map lines are stored in a linked list for flexible processing
- Empty lines before the first map line are skipped
- Empty lines within or after the map contribute to map structure

**Phase 3: Map Validation and Structure Building**

The accumulated map lines are consolidated into a 2D character array with four critical validations:

1. **Width Normalization**: All rows are padded to equal width for consistent indexing
2. **Unique Spawn Point**: Exactly one player position (N, S, E, or W) must exist
   - N = Player facing North
   - S = Player facing South
   - E = Player facing East
   - W = Player facing West
3. **Spatial Closure Verification** (Flood-fill algorithm):
   - Starts from player position and reaches all accessible non-wall spaces
   - Confirms all reachable areas are enclosed by walls (no map edges or holes)
   - Prevents players from leaving the map boundaries
4. **Spawn Position Safety**: Player cannot begin on map boundaries

**Valid Map Characters:**
- `0` = Empty walkable space
- `1` = Solid wall
- `N/S/E/W` = Player spawn point and initial direction

### 2. DDA Algorithm (Digital Differential Analyzer)

The DDA algorithm efficiently traverses a 2D grid to find ray-wall intersections without expensive trigonometry.

**How it works:**

1. **Initialize the ray**: Starting from player position with a specific angle
2. **Calculate step directions**: Determine whether to move horizontally or vertically first
3. **Grid traversal loop**:
   - Compare distances to next horizontal and vertical grid lines (tmax_x and tmax_y)
   - Move in the direction with the smaller distance
   - Continue until a wall is detected
4. **Collision type determination**: Was the collision on a horizontal or vertical surface?

**Advantages:**
- No expensive trigonometric calculations
- Fast grid traversal with simple additions and comparisons
- Accurate collision detection

### 3. Raycasting Rendering

Raycasting converts the 2D map into a 3D first-person view by casting 800 rays (one per screen column).

**Rendering pipeline for each column:**

1. **Cast ray**: Send a ray from player position at a specific angle
2. **Find collision**: Use DDA to locate the nearest wall
3. **Calculate distance**: Compute perpendicular distance (prevents fisheye distortion)
4. **Determine wall height**: `wall_height = screen_height / distance`
5. **Texture mapping**: Calculate UV coordinates to fetch the correct texture pixel
6. **Render column**: Fill screen column with textured wall data

**Fisheye Correction:**
Without correction, rays at screen edges would be longer, causing the image to bulge. Using perpendicular distance instead of direct ray distance fixes this.

## Architecture

The project is organized into modular components respecting the 42 Norminette constraints (max 5 functions per file, max 25 lines per function). Each module handles a specific responsibility:

### Core Modules

| Module | Purpose | Key Files |
|--------|---------|-----------|
| **raycasting/** | 3D rendering engine using DDA and raycasting | `raycasting.c`, `dda_algo.c`, `draw_vertical_line.c` |
| **parsing/** | Configuration file parsing and validation | `parse_file.c`, `check_map.c`, `parse_color.c` |
| **textures/** | Texture loading and pixel access management | `charge_textures.c`, `texture_loader.c` |
| **render_3d/** | Floor and ceiling rendering | `render.c`, `draw_floor_and_ceilling.c` |
| **player/** | Player position, direction, and collision handling | `update_player.c`, `wall_collision_bonus.c` |
| **keyboard/** | Keyboard input event handling | `handle_key.c` |
| **window/** | Window creation and event management | `open_window.c`, `window_events.c` |
| **game/** | Main game state initialization and loop | `init_data_game_key.c` |
| **minimap/** | Optional minimap rendering | `draw_minimap_bonus.c` |

### Module Details

**Keyboard Module (`keyboard/`)**
- Single handler `handle_key.c` processes KeyPress and KeyRelease events
- Updates global key array in game state
- Direct Escape key handling for window close
- Simplified design without helper functions for cleaner code

**Window Module (`window/`)**
- `open_window.c`: Initializes MLX window, image buffer, and hooks
- `window_events.c`: Manages core window events (close only)
- Minimalist approach focusing on essential window management

**Raycasting Module (`raycasting/`)**
- `raycasting.c`: Main orchestrator - loops through 800 rays
- `init_ray.c`: Ray initialization based on camera angle
- `calculate_step.c`: DDA step calculations
- `dda_algo.c`: Grid traversal algorithm
- `calculate_wall_distance.c`: Perpendicular distance computation
- `draw_vertical_line.c`: Screen column rendering with textures

## Resources

### Raycasting and DDA Algorithm References

1. **DDA - Interactive Explanation**
   https://aaaa.sh/creatures/dda-algorithm-interactive/
   
2. **DDA Line Generation Algorithm - GeeksforGeeks**
   https://www.geeksforgeeks.org/computer-graphics/dda-line-generation-algorithm-computer-graphics/

3. **Raycasting Tutorial - LoDevInfo**
   https://lodev.org/cgtutor/raycasting.html

4. **Raycasting Game Tutorial - YouTube**
   https://www.youtube.com/watch?v=G9i78WoBBIU

5. **Raycasting: From Doom to Wolfenstein**
   https://guy-grave.developpez.com/tutoriels/jeux/doom-wolfenstein-raycasting/

6. **Raycasting - Wikipedia**
   https://fr.wikipedia.org/wiki/Raycasting

7. **Cub3D Implementation Reference - Nathaan**
   https://nathaan.me/projects/cub3d

### AI Usage

AI was used for learning and documentation purposes:
- **Raycasting and DDA concepts**: Understanding and explaining raycasting rendering technique and the DDA algorithm with reference to educational tutorials and articles
- **Function naming clarity**: Ensuring descriptive names that communicate purpose clearly
- **README documentation**: Structuring technical explanations for clarity and coherence
- **Parsing logic explanation**: Documenting the three-phase parsing process and validation steps

## Compilation Status

- **Binary size**: ~327KB (optimized: `-O3`)
- **Norminette compliance**: Raycasting module 100% compliant (10/10 files)
- **Warnings**: None
- **Tested maps**: Library, classic, and edge cases all functional

## Summary

Cub3D demonstrates a working 3D raycasting engine that implements:
- **DDA algorithm** for efficient ray-grid intersection
- **Raycasting** to convert 2D maps to 3D perspectives
- **Texture mapping** for realistic wall rendering
- **Modular architecture** compliant with strict coding standards

