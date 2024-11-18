# Interactive Turtle Graphics Program

## Overview
This project is an **Interactive Turtle Graphics** program written in C, using **SDL2** for window management and **OpenGL** for rendering graphics. Inspired by the concept of turtle graphics, it allows users to control a "turtle" sprite to create line drawings on a 2D canvas by moving, rotating, and drawing based on user input.

The project provides an interactive way to learn about graphics programming, user inputs, and drawing with **OpenGL** and **SDL2**.

## Features
- **Control a Turtle Sprite**: Use keyboard input to move the turtle forward or rotate it in different directions.
- **Draw Lines**: The turtle can either draw lines while moving (when the pen is down) or move without drawing (when the pen is up).
- **Interactive Graphics Rendering**: The program uses **OpenGL** to render the turtle sprite and the drawn lines efficiently.
- **Customizable Turtle Sprite**: The turtle is represented by an image that can be customized by modifying the `IMG` macro.

## Controls
- **Arrow Keys**:
  - `←` (Left Arrow): Rotate the turtle **45 degrees** to the left.
  - `→` (Right Arrow): Rotate the turtle **45 degrees** to the right.
  - `↑` (Up Arrow): Move the turtle forward by a set distance.
- **Pen Control**:
  - `d` - **Pen Down**: The turtle will draw lines as it moves.
  - `u` - **Pen Up**: The turtle will move without drawing.
- **Escape Key**:
  - `Esc`: Exit the program.

## Setup and Compilation

### Prerequisites
Make sure you have the following libraries installed on your system:
- **SDL2**: Required for window management and event handling.
- **OpenGL**: Used for rendering graphics.

### Compilation
Use the provided `Makefile` to compile the program. Run the following command in the terminal:

```sh
make
```

Alternatively, you can manually compile the program using gcc:

```sh
gcc ./src/mega.o -o ./Binaries/turtle -lSDL2 -lGL -lGLU -ldl -lm
```

### Running the program
After compiling, run the executable:

```sh
./Binaries/turtle
```

## Code Structure

### Libraries Used
- **SDL2**: Used for window creation, input handling, and loading BMP images for the turtle sprite.
- **OpenGL**: Utilized for drawing graphics on the screen, including lines and the turtle sprite.

### Main Components
- **Sprite Movement and Orientation**: The turtle moves forward based on its current orientation, and can rotate left or right in **45-degree** increments.
- **Drawing Lines**: The turtle draws lines when the pen is down, with coordinates for all lines stored and redrawn every frame for persistence.
- **Rendering**: The rendering loop clears the screen, draws all lines, and then draws the turtle at its current position. Double buffering is used for smooth rendering.

### How It Works
The program starts by initializing **SDL2** and creating a window with an **OpenGL** rendering context. The turtle sprite image is loaded and displayed in the window.

The **event loop** runs continuously, checking for user input to move or rotate the turtle, or change the pen state. When the turtle moves with the pen down, a line is drawn from the previous location to the new location. **OpenGL** rendering functions are used to render both the turtle and any drawn lines.

#### Rendering Pipeline
- **Line Drawing**: All drawn lines are stored in an array and redrawn every frame using **OpenGL**'s `glBegin(GL_LINES)` function.
- **Sprite Rendering**: The turtle sprite is rendered using `glDrawPixels()` to display the image at the current location.

### File Structure
- **`src/`**: Contains the source code files.
- **`Images/`**: Contains the BMP file representing the turtle sprite.
- **`Binaries/`**: Contains the compiled output of the program.

### Dependencies
The program depends on the following libraries:
- **SDL2**: Simple DirectMedia Layer for managing the window, handling user input, and loading images.
- **OpenGL (GL and GLU)**: Graphics library for rendering lines and the turtle sprite.
- **Math Library** (`math.h`): Provides trigonometric functions for calculating movement.

### Customization
- **Sprite Image**: To change the turtle sprite image, replace the BMP file specified by the `IMG` macro.
- **Movement Distance**: Modify the `MOVE_DISTANCE` macro to change how far the turtle moves with each step.
- **Window Size**: The window dimensions are currently set to **800x800** pixels. Adjust these values in the `SDL_CreateWindow()` call to change the size.

### Limitations
- The program currently supports the **BMP** image format for the turtle sprite.
- The number of lines that can be drawn is limited to **1000**. This can be increased by modifying the `lines` array or by implementing a dynamic storage system.
- **Orthographic Projection**: Uses orthographic projection, suitable for 2D graphics but not for 3D.

### Future Improvements
- **Dynamic Line Storage**: Implement dynamic memory allocation for lines to allow unlimited drawing.
- **Enhanced Controls**: Add smoother rotation and more precise movement control.
- **Support for More Image Formats**: Add support for additional image formats, such as **PNG** and **JPEG**.
- **User Interface**: Add an on-screen UI for displaying the current state (pen up/down, angle, etc.).
