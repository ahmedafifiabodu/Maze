# Simple Maze Solutions

## Overview

This project showcases two distinct maze solutions: Static and Dynamic. The Static maze is a fixed layout offering a straightforward navigation challenge, while the Dynamic maze evolves over time, providing a more complex and engaging experience. This project aims to explore various maze generation algorithms and player interaction within these mazes.

## Features

- **Static Maze Solution**: A pre-defined maze layout that does not change.
- **Dynamic Maze Solution**: A maze that evolves as the player progresses, offering a unique experience each time.
- **Maze Variants**: Exploration of different maze generation algorithms including Aldous-Broder Maze, Final Maze, Maze, New Maze, and Perfect Maze.
- **Player Interaction**: Manage player movement and animations within the maze.
- **Coin Collection**: Dynamic mazes include coin collection mechanics to enhance gameplay.

## Simple Maze (Static)

The Static version of the maze is a fixed layout that does not change over time. It focuses on navigating through a predefined maze structure.

### Key Components:

- **DrawGrid**: Responsible for drawing the maze grid on the screen.
  - [DrawGrid.cpp](#simple-maze-(static)\drawgrid.cpp-context)
  - [DrawGrid.h](#simple-maze-(static)\drawgrid.h-context)
- **Player**: Manages the player's position, movement, and animations within the maze.
  - [Player.cpp](#simple-maze-(static)\player.cpp-context)
  - [Player.h](#simple-maze-(static)\player.h-context)
- **PlayerAnimation**: Handles the animation of the player character.
  - [PlayerAnimation.cpp](#simple-maze-(static)\playeranimation.cpp-context)
  - [PlayerAnimation.h](#simple-maze-(static)\playeranimation.h-context)
- **Main**: The entry point of the application.
  - [src\main.cpp](#simple-maze-(static)\src\main.cpp-context)

## Simple Maze (Dynamic)

The Dynamic version introduces an evolving maze that changes as the player progresses, offering a more challenging and engaging experience.

### Key Components:

- **CellDimension**: Defines the dimensions of the maze cells.
  - [CellDimension.h](#celldimension.h-context)
- **Coin**: Manages the coin animations and interactions within the maze.
  - [Coin.cpp](#coin.cpp-context)
  - [Coin.h](#coin.h-context)
- **CoinAnimation**: Handles the animation of the coins.
  - [CoinAnimation.cpp](#coinanimation.cpp-context)
  - [CoinAnimation.h](#coinanimation.h-context)
- **DrawGrid**: Responsible for drawing the dynamic maze grid on the screen.
  - [DrawGrid.cpp](#simple-maze-(dynamic)\drawgrid.cpp-context)
  - [DrawGrid.h](#simple-maze-(dynamic)\drawgrid.h-context)
- **Player**: Manages the player's position, movement, and animations within the dynamic maze.
  - [Player.cpp](#simple-maze-(dynamic)\player.cpp-context)
  - [Player.h](#simple-maze-(dynamic)\player.h-context)
- **PlayerAnimation**: Handles the animation of the player character in the dynamic maze.
  - [PlayerAnimation.cpp](#simple-maze-(dynamic)\playeranimation.cpp-context)
  - [PlayerAnimation.h](#simple-maze-(dynamic)\playeranimation.h-context)
- **RandomArray**: Utilized for generating the dynamic maze.
  - [RandomArray.cpp](#randomarray.cpp-context)
  - [RandomArray.h](#randomarray.h-context)

## Maze Variants Explored

Throughout the development of this project, various types of mazes were explored, including:

- Aldous-Broder Maze

<div align="center">
  <video src="https://github.com/ahmedafifiabodu/SFML-Maze-Game/assets/74466733/0f74ee1a-4c5e-4b07-9a8f-9778e083f0a2" width="800" />
</div>

- Final Maze

<div align="center">
  <video src="https://github.com/ahmedafifiabodu/SFML-Maze-Game/assets/74466733/e79517fc-6a69-4b17-9e3f-eb44e995299a" width="800" />
</div>

- Maze

<div align="center">
  <img src="https://github.com/ahmedafifiabodu/SFML-Maze-Game/assets/74466733/b785a563-16ce-4e5a-a5da-89db19763f92" width="800" />
</div>

- New Maze

<div align="center">
  <img src="https://github.com/ahmedafifiabodu/SFML-Maze-Game/assets/74466733/28f1429f-f0f6-4cfe-875d-6d041294e759" width="800" />
</div>
  
- Perfect Maze

- <div align="center">
  <img src="https://github.com/ahmedafifiabodu/SFML-Maze-Game/assets/74466733/2c1f0b7c-2bbe-4a43-84ee-219442d42f0f" width="800" />
</div>

These variants provided a comprehensive understanding of maze generation algorithms and their applications in game development.

## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

- A modern C++ compiler that supports C++20.
- An IDE or editor that supports C++ development (e.g., Visual Studio 2022).

### Installation

1. Clone the repo
2. Open the project in your IDE or editor.
3. Build the project to ensure everything is set up correctly.
4. Run the project to start exploring the mazes.

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the MIT License. See `LICENSE` for more information.
