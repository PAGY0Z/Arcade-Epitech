|          Test         | Pourcentage | Succès/Nombre de Tests |
|:-------------------------:|:----------:|:---------------:|
|        Preliminaries        |    100 %   |      2 / 2      |
|        Dynamic Linking Library encapsulation        |    100 %   |      1 / 1      |
|        Dynamic library change        |    100 %   |      1 / 1      |
|        Games interface genericity        |    100 %   |      0.5 / 0.5      |
|        Game interface independency        |    100 %   |      0.5 / 0.5      |
|        Graphic interface genericity        |    100 %   |      0.5 / 0.5      |
|        Graphic interface independency        |    100 %   |      0.5 / 0.5      |
|        Pure virtual interfaces        |    100 %   |      0.5 / 0.5      |
|        Libraries list        |    100 %   |      0.5 / 0.5      |
|        Menu library        |    100 %   |      0.5 / 0.5      |
|        Scores        |    100 %   |      0.5 / 0.5      |
|        Player name        |    50 %   |      0.25 / 0.5      |
|        Game loop        |    50 %   |      0.25 / 0.5      |
|        nCurses (arcade_ncurses.so)        |    50 %   |      0.75 / 1.5      |
|        SDL2 (arcade_sdl2.so)        |    83.3 %   |      1.25 / 1.5      |
|        Third library        |    83.3 %   |      1.25 / 1.5      |
|        Game #1        |    60 %   |      0.9 / 1.5      |
|        Game #2        |    40 %   |      0.6 / 1.5      |
|        Collaboration        |    100 %   |      1 / 1      |
|        Documentation        |    100 %   |      0.5 / 0.5      |
|        Exception        |    100 %   |      1 / 1      |
|        Template        |    50 %   |      0.5 / 1      |
|        Memory management        |    0 %   |      0 / 1      |
|        **Résultats**        | **77.38 %** |     **16.25 / 21**     |

[![Arcade Workflow](https://github.com/PAGY0Z/Arcade-Epitech/actions/workflows/Arcade_wokflow.yml/badge.svg)](https://github.com/PAGY0Z/Arcade-Epitech/actions/workflows/Arcade_wokflow.yml)
[![pages-build-deployment](https://github.com/PAGY0Z/Arcade-Epitech/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/PAGY0Z/Arcade-Epitech/actions/workflows/pages/pages-build-deployment)

# Arcade Project by Onestla & Le Pacman, Le Snake Et Le Centipède

Welcome to our Arcade project, a collaborative creation by two enthusiastic groups from Epitech, designed for the Object Oriented Programming module. This project brings classic games like Pacman, Snake, and others to life, wrapped in a modern and flexible architecture that allows easy swapping between games and graphical libraries.

## Team Members

**Onestla:**
- Etienne Techer - etienne.techer@epitech.eu
- Mathys Sartre - mathys.sartre@epitech.eu
- Pierre-Alexandre GROSSET - pierre-alexandre.grosset@epitech.eu

**Le Pacman, Le Snake Et Le Centipède:**
- Florian Dajon - florian.dajon@epitech.eu
- Amdjad Ahmod-Ali - amdjad.adhmod-ali@epitech.eu
- Romain Nacaouele - romain.nacaouele@epitech.eu

## How to Play

Navigate through our arcade with ease, choosing between our array of games and graphical libraries, setting new high scores, and enjoying a seamless gaming experience.

### Menu Navigation
- **Arrow keys:** Navigate through games and graphics libraries.
- **Enter:** Start selected game with chosen graphics library.
- **Escape:** Exit the program.
- **Alphanumeric keys:** Enter player name.
- **SFML specific:** Use mouse clicks for navigation.

### Game Controls
- **Arrow keys:** Move in-game characters.
- **Escape:** Exit the program.
- **Keypad 4 & 6:** Switch graphic libraries.
- **Keypad 8 & 2:** Switch games.
- **Keypad 5:** Reload the game.
- **Keypad 0:** Return to the menu.

## Getting Started

### Prerequisites
Ensure you have `ncurses`, `sfml`, `sdl2`, and `sdl2_image` installed on your computer.

### Compilation and Execution
- **Compile:** `./compile.sh` or manually via CMake.
- **Launch:** `./arcade ./lib/arcade_[lib].so`.
- **Clean:** `./clear.sh` or manually remove build artifacts.

### Documentation and UML
- Access the project's subject and bootstrap files for detailed guidelines.
- Browse the `./docs/` directory for comprehensive documentation.
- View and modify the UML diagrams using StarUML.

## Enjoy and Have Fun!
Dive into the nostalgia of classic arcade games with a modern twist. Set new high scores, explore different graphical interfaces, and immerse yourself in the arcade experience. Your feedback and contributions are welcome as we continue to improve and expand our project.

# Graphics Library Implementation Guide

This document outlines the structure and implementation guide for a new graphics library, drawing inspiration from the structure of the SFML library. The goal is to keep the design simple and fast, focusing on essential functionalities such as window management, display data retrieval, game data reception, and texture management.

## Overview

The proposed library will consist of several key components designed to manage graphic displays and handle events efficiently. Below is a detailed description of the methods and structures involved:

### 1. Window State Check

```cpp
bool getIsRunning() const final;
```

- **Purpose**: Determines if the window is currently open.
- **Implementation Notes**: Relies on the underlying library method (e.g., `sf::RenderWindow.isOpen()` in SFML) to check the window's state.

### 2. Display Data Retrieval

```cpp
const struct DisplayData &getDisplayData() const final;
```

- **Purpose**: Fetches data related to the graphic display and window-related events.
- **Details**:
    - Returns an instance of `struct DisplayData`, which includes:
        - A `std::vector<AEvent>` for event handling.
        - A `float delta` representing the elapsed time between two frames.
    - The method of retrieving `deltaTime` is library-dependent (e.g., `getElapsedTime().asSeconds()` in SFML).

```cpp
struct DisplayData
{
    std::vector<AEvent> events;
    float delta;
};
```

### 3. Game Data Reception

```cpp
void receiveGameData(const struct GameData &data) final;
```

- **Purpose**: Updates the graphic display based on received game data.
- **Requirements**:
    - Resize and set the window view according to game screen dimensions.
    - Center the window on the screen.
    - Erase previous window content and update map textures with provided data.
    - Display content and manage memory efficiently.
- **For Each Entity**:
    - Create and draw SFML sprites based on entity properties and available textures.

```cpp
struct GameData
{
    std::vector<AEntity> entities;
    std::map<char, std::string> textures;
    std::size_t screen_size_x;
    std::size_t screen_size_y;
};
```

### 4. Texture Map Update

```cpp
void update_texture_map(std::map<char, std::string> textures);
```

- **Purpose**: Updates the map of textures used by the graphics application.
- **Implementation**:
    - Checks for the presence of textures in the `_textures` map.
    - Loads new textures from file paths if not already present, throwing a `GraphicSFMLException` for loading failures.
    - Safely adds new textures to the `_textures` map.

**Exception Handling**:
- In case of `AException` or derived exceptions, the error message is displayed, and the `_window` window is closed.

## Conclusion

This implementation guide provides a structured approach to building a graphics library that is both efficient and easy to use. By following the guidelines outlined above, developers can ensure a smooth and dynamic graphical interface for their applications. The proposed design is flexible and extensible, allowing for future enhancements and modifications as needed.

Below is a Markdown rendition of the `IGameModule` interface documentation:

## Game Library Implementation Guide

This document outlines the structure and implementation guide for a new game library. The goal is to ensure a robust, efficient, and flexible foundation for game development, focusing on essential functionalities such as state management, data exchange with the graphics library, and event handling.

### Overview

The proposed game library will consist of several key components designed to manage game states, interact with graphic displays, and handle user input effectively. Below is a detailed description of the methods and structures involved:

### 1. Game State Check

```cpp
bool getIsRunning() const override;
```

- **Purpose**: Determines if the game is currently running.
- **Implementation Notes**: This method returns the current state of the game, allowing external systems to check if the game loop should continue.

### 2. Display Data Reception

```cpp
void receiveDisplayData(const struct DisplayData &data) override;
```

- **Purpose**: Receives and processes display data from the graphics library.
- **Details**:
    - Handles events from the `std::vector<AEvent>` within `DisplayData`.
    - Uses the `float delta` to manage time-sensitive game logic, such as movement and animations.

### 3. Game Data Provision

```cpp
const struct GameData &getGameData() const override;
```

- **Purpose**: Provides game data to the graphics library for rendering.
- **Details**:
    - Returns an instance of `struct GameData`, which includes:
        - A collection of game entities.
        - A map of character-to-texture mappings for rendering.
        - Screen dimensions for view adjustments.

### 4. System Event Handling

```cpp
std::vector<AEvent> getSystemEvents() const override;
```

- **Purpose**: Provides a list of system-wide events (e.g., keyboard, mouse) to the main application.
- **Implementation Notes**: This method should gather and return all relevant events for further processing by the main application or other libraries.

### 5. Player Information Management

```cpp
std::string getPlayerName() const override;
void setPlayerName(const std::string &name) override;

int getScore() const override;
void setScore(int score) override;

int getHighscore() const override;
void setHighscore(int highscore) override;
```

- **Purpose**: Manages player-related information, including the player's name, current score, and high score.
- **Implementation Notes**: These methods allow for the storing, updating, and retrieval of player-specific data, which can be used for display, logging, or comparison purposes.

### 6. Game Configuration

```cpp
std::string getGameName() const override;
void setGameName(const std::string &game_to_load) override;

std::string getGraphicName() const override;
void setGraphicName(const std::string &graphic_to_load) override;
```

- **Purpose**: Configures the game and graphics module names.
- **Implementation Notes**: These methods facilitate the dynamic loading and unloading of game and graphic modules, supporting a flexible and modular architecture.

## Conclusion

This implementation guide provides a comprehensive framework for developing a game library that is compatible with a graphics library like SFML. By following the outlined structures and methods, developers can create a game library that efficiently handles game logic, player data, and interactions with graphical interfaces. The design is intended to be flexible, allowing for easy expansion and adaptation to fit specific project requirements.
