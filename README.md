*This project has been created as part of the 42 curriculum by cecompte and esergeev.*

# cub3D - A Raycasting 3D Graphics Engine

## Description

cub3D is a school project that implements a raycasting engine to create a 3D graphical representation of a maze from a first-person perspective. This project introduces fundamental concepts of computer graphics, particularly raycasting algorithms, which were popularized in games like Wolfenstein 3D.

### Project Goal

The primary goal is to develop a functional raycasting renderer capable of:
- Parsing a configuration file describing a 3D environment (map layout, textures, colors)
- Rendering a real-time 3D view from the player's perspective
- Handling player movement and rotation through keyboard input
- Displaying textured walls and handling sprite rendering (bonus part)
- Managing minimap display and advanced features (bonus part)

### Overview

The engine reads a `.cub` configuration file that defines the map layout and visual properties, then renders an interactive 3D environment using the minilibx graphics library. The player can navigate through the maze using keyboard controls and experience a dynamic 3D perspective.

---

## Instructions

### Requirements

- **Linux-based system** (tested on systems with X11 support)
- **C compiler** (CC) with support for C99 standard
- **minilibx** graphics library (included in the project)
- **Make** build tool

### Compilation

```bash
# Build the mandatory version
make

# Build with all bonus features
make bonus

# Clean object files
make clean

# Remove all generated files including executable
make fclean

# Rebuild everything from scratch
make re
```

### Installation

The project is self-contained and does not require external installation beyond system dependencies:

```bash
# Ensure X11 development libraries are installed (Ubuntu/Debian example)
sudo apt-get install libx11-dev libxext-dev

# Clone or navigate to the repository
cd cub3d
make
```

### Execution

```bash
# Run the mandatory version with a configuration file
./cub3D maps/valid/<map_name>.cub

# Run the bonus version
./cub3D_bonus maps_bonus/<map_name>.cub
```

### Configuration File Format

Map files must be `.cub` files with the following required elements:

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm
F 220,100,0
C 225,30,0
1111111111
1000000001
1000000001
1000000001
1111111111
```

- **NO, SO, WE, EA**: Paths to wall textures
- **F**: Floor color (RGB)
- **C**: Ceiling color (RGB)
- **Map**: Grid where `1` = wall, `0` = empty space, `N/S/E/W` = player start position

### Controls

- **W / Up Arrow**: Move forward
- **S / Down Arrow**: Move backward
- **A**: Strafe left
- **D**: Strafe right
- **Left Arrow / Right Arrow**: Rotate camera left/right
- **ESC**: Exit the program

---

## Features

### Mandatory Features

- ✓ Configuration file parsing (`.cub` format)
- ✓ Raycasting algorithm implementation
- ✓ Textured wall rendering
- ✓ Real-time first-person perspective
- ✓ Smooth player movement and camera rotation
- ✓ Error handling for invalid maps and configurations

### Bonus Features

- ✓ Additional wall textures support
- ✓ Sprite rendering and animation
- ✓ Door mechanics
- ✓ Minimap display
- ✓ Enhanced graphics effects

---

## Resources

### Documentation & References

- **Raycasting Fundamentals**: [Permadi.com - Raycasting Engine](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) - Comprehensive guide to raycasting techniques used in this project
- **minilibx Documentation**: Included in `minilibx-linux/` directory with function reference and examples


## Technical Details

### Architecture

The project is organized into logical modules:

- **Parsing**: Configuration and map file parsing (`parce_config.c`, `map.c`)
- **Rendering**: Core raycasting and texture rendering (`render.c`, `rays.c`)
- **Gameplay**: Player movement and collision detection (`movements.c`, `map_grid_utils.c`)
- **Utilities**: Helper functions for memory and string operations (`libft/`)
- **Graphics**: Texture and image operations (`texture_operation.c`)

### Build System

- Separate compilation targets for mandatory and bonus versions
- Dependency tracking with `-MMD -MP` flags
- Integration with minilibx static library
- Support for both debug (`-g3`) and production builds

---

## 42 School Information

This project is part of the mandatory curriculum at 42, a software engineering school. It demonstrates practical application of computer graphics concepts and low-level programming skills in C.