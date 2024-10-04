# Snake Game

A classic Snake game implemented in C++ using the SFML (Simple and Fast Multimedia Library) framework. The game features a playable snake that grows in size as it consumes food while navigating a grid-based map filled with walls. Players can control the direction of the snake using the arrow keys and can pause the game at any time.

## Features

- **Gameplay**: 
  - Control the snake using arrow keys (Up, Down, Left, Right).
  - The game ends if the snake collides with itself or with walls.
  - Score increases with each food item consumed.

- **Map Design**:
  - The map is represented using a 2D array, allowing for easy modification and extension.
  - Walls are visually represented in the game.

- **Graphics**:
  - Utilizes SFML for rendering graphics, including textures for the snake, food, and background.
  - Customizable menu interface with "Play" and "Exit" options.

- **Pause Functionality**: 
  - The game can be paused by pressing the 'P' key.

## Installation

1. Make sure you have [SFML](https://www.sfml-dev.org/download.php) installed on your system.
2. Clone this repository or download the source code files.
3. Open the project in your preferred C++ IDE (e.g., Visual Studio).
4. Link the SFML libraries in your project settings.
5. Place the required font file (`Tron.ttf`) and texture images (`image2.png`, `image3.png`) in the project directory.

## How to Play

1. Build and run the project in your IDE.
2. Click on "Play" in the menu to start the game.
3. Use the arrow keys to control the snake.
4. Avoid colliding with walls or the snake's own body.
5. Press 'P' to pause the game.
6. Click "Exit" to close the game.

## Controls

- **Arrow Keys**: Control the direction of the snake.
- **P**: Pause/Resume the game.
- **Escape**: Exit the game.

## Code Structure

- `main.cpp`: The main entry point of the game, handles game logic, rendering, and event management.
- `convert_sketch`: Converts a string-based map sketch into a 2D array representation.
- `draw_map`: Renders the map on the screen.

## Acknowledgments

- Developed using the SFML library for graphics handling.
- Inspired by the classic Snake game mechanics.
