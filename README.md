# miniRT - 3D Ray Tracing Engine

## Description
A minimalist ray tracing renderer implemented in C using MinilibX library. This project creates photorealistic 3D scenes by simulating light behavior and rendering basic geometric shapes.

## Features
- Ray tracing implementation from scratch
- Basic geometric shapes (spheres, planes, cylinders)
- Light effects (ambient, diffuse, specular)
- Shadow calculation
- Scene parsing from .rt files
- Camera positioning and FOV control

## Requirements
- GCC compiler
- Make
- MinilibX library
- X11 development files (for Linux)

## Building Instructions

### Prerequisites
```bash
# Install required packages on Ubuntu/Debian
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Clone the repository
git clone https://github.com/yourusername/miniRT.git
cd miniRT

# Build the project
make
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild the project
```
## File Format


# Elements

- A Ambient lighting:
```bash
A [light ratio 0.0-1.0] [R,G,B (0-255)]
A 0.2 255,255,255
```
- C Camera:
```bash
C [x,y,z position] [3d vector] [FOV 0-180]
C -50.0,0,20 0,0,1 70
```
- L Light:
```bash
L [x,y,z position] [brightness 0.0-1.0] [R,G,B]
L -40.0,50.0,0.0 0.6 10,0,255
```
# Shapes

- sp Sphere:
```bash
sp [x,y,z center] [diameter] [R,G,B]
sp 0.0,0.0,20.6 12.6 10,0,255
```
- pl Plane:
```bash
pl [x,y,z point] [normal vector] [R,G,B]
pl 0.0,0.0,-10.0 0.0,1.0,0.0 255,0,225
```
- cy Cylinder:
```bash
cy [x,y,z center] [vector] [diameter] [height] [R,G,B]
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
```
## Example Scene File
```bash
# Comments start with #
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
sp 0,0,20 20 255,0,0
pl 0,-10,0 0,1,0 255,255,0
cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255
```

## Running
```bash
./miniRT scenes/example.rt
```

## License and Credits

This project is part of the 42 School curriculum. All rights reserved.

## Third-Party Components

1. MinilibX library - 42 School
2. Math functions from the C Standard Library

## Authors

### Core Development Team

| Developer | Role | GitHub |
|-----------|------|--------|
| Salah Gouzi | Core Developer | [@sgouzi](https://github.com/gouzidev) |
| Yassir Sbai | Core Developer | [@ysbai](https://github.com/VICTORxEVO) |

---

This project was developed as part of the 42 School curriculum.

For questions or feedback, please reach out to the development team through GitHub.