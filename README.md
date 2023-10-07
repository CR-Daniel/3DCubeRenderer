# 3D Cube Renderer

A simple C++ application using OpenGL to render a rotating 3D cube.

![Alt text](clip.gif)

## Features

- **Rotating 3D Cube**: The cube rotates automatically.
- **OpenGL Integration**: Uses OpenGL for 3D rendering.
- **Customizable**: Easily modify the code to change the cube's color, size, rotation speed, etc.

## Prerequisites

- C++ Compiler (Recommend GCC)
- OpenGL Library
- GLEW (OpenGL Extension Wrangler Library)
- GLFW (Graphics Library Framework)
- GLM (OpenGL Mathematics)

## Building & Running

1. Clone this repository.

2. Navigate to the project directory:
   ```sh
   cd 3DCubeRenderer
   ```

3. Compile the program:
   ```sh
   g++ cube.cpp -o cube -lGL -lGLEW -lglfw -std=c++11
   ```

4. Run the application:
   ```sh
   ./cube
   ```