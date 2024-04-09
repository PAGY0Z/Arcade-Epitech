add_compile_options(-W -Wall -Wextra -Werror)

# Menu
add_library(game_menu SHARED
        ../src/common/AEntity.cpp
        ../src/common/AEvent.cpp
        ../src/common/AException.cpp
        src/games/AGame.cpp
        src/games/Menu/GameMenu.cpp
        ../includes/common/AEntity.hpp
        ../includes/common/AEvent.hpp
        ../includes/common/AException.hpp
        includes/games/AGame.hpp
        includes/games/Menu/GameMenu.hpp
        ../includes/game/IGameModule.hpp
)

set(GAME_MENU_INCLUDE_DIR ../includes/common ../includes/game includes/games includes/games/Menu)
target_include_directories(game_menu PUBLIC ${GAME_MENU_INCLUDE_DIR})
set_target_properties(game_menu PROPERTIES OUTPUT_NAME "arcade_menu" PREFIX "")

# Pacman
add_library(game_pacman SHARED
        ../src/common/AEntity.cpp
        ../src/common/AEvent.cpp
        ../src/common/AException.cpp
        src/games/AGame.cpp
        src/games/Pacman/GamePacman.cpp
        ../includes/common/AEntity.hpp
        ../includes/common/AEvent.hpp
        ../includes/common/AException.hpp
        includes/games/AGame.hpp
        includes/games/Pacman/GamePacman.hpp
        ../includes/game/IGameModule.hpp

        includes/games/Pacman/Ghost.hpp
        src/games/Pacman/Ghost.cpp

        includes/games/Pacman/Pacgum.hpp
        src/games/Pacman/Pacgum.cpp

        includes/games/Pacman/Player.hpp
        src/games/Pacman/Player.cpp

        includes/games/Pacman/Wall.hpp
        src/games/Pacman/Wall.cpp

        includes/games/Pacman/Teleporter.hpp
        src/games/Pacman/Teleporter.cpp
)

set(GAME_PACMAN_INCLUDE_DIR ../includes/common ../includes/game includes/games includes/games/Pacman)
target_include_directories(game_pacman PUBLIC ${GAME_PACMAN_INCLUDE_DIR})
set_target_properties(game_pacman PROPERTIES OUTPUT_NAME "arcade_pacman" PREFIX "")

# Snake
add_library(game_snake SHARED
        ../src/common/AEntity.cpp
        ../src/common/AEvent.cpp
        ../src/common/AException.cpp
        src/games/AGame.cpp
        src/games/Snake/GameSnake.cpp
        ../includes/common/AEntity.hpp
        ../includes/common/AEvent.hpp
        ../includes/common/AException.hpp
        includes/games/AGame.hpp
        includes/games/Snake/GameSnake.hpp
        ../includes/game/IGameModule.hpp

        includes/games/Snake/Apple.hpp
        includes/games/Snake/GameSnake.hpp
        includes/games/Snake/Snake.hpp

        src/games/Snake/Apple.cpp
        src/games/Snake/GameSnake.cpp
        src/games/Snake/Snake.cpp
)

set(GAME_SNAKE_INCLUDE_DIR ../includes/common ../includes/game includes/games includes/games/Snake)
target_include_directories(game_snake PUBLIC ${GAME_SNAKE_INCLUDE_DIR})
set_target_properties(game_snake PROPERTIES OUTPUT_NAME "arcade_snake" PREFIX "")


##############################################################################

# nCurses
add_library(graphic_ncurses SHARED
        ../src/common/AEntity.cpp
        ../src/common/AEvent.cpp
        ../src/common/AException.cpp
        src/graphics/AGraphic.cpp
        src/graphics/nCurses/GraphicNCurses.cpp
        ../includes/common/AEntity.hpp
        ../includes/common/AEvent.hpp
        ../includes/common/AException.hpp
        includes/graphics/AGraphic.hpp
        includes/graphics/nCurses/GraphicNCurses.hpp
        ../includes/display/IDisplayModule.hpp
)

set(GRAPHIC_NCURSES_INCLUDE_DIR ../includes/common ../includes/display includes/graphics includes/graphics/nCurses)
target_include_directories(graphic_ncurses PUBLIC ${GRAPHIC_NCURSES_INCLUDE_DIR})
set_target_properties(graphic_ncurses PROPERTIES OUTPUT_NAME "arcade_ncurses" PREFIX "")
find_package(Curses REQUIRED)
target_link_libraries(graphic_ncurses ncurses)

# SDL2
add_library(graphic_sdl2 SHARED
        ../src/common/AEntity.cpp
        ../src/common/AEvent.cpp
        ../src/common/AException.cpp
        src/graphics/AGraphic.cpp
        src/graphics/SDL2/GraphicSDL2.cpp
        ../includes/common/AEntity.hpp
        ../includes/common/AEvent.hpp
        ../includes/common/AException.hpp
        includes/graphics/AGraphic.hpp
        includes/graphics/SDL2/GraphicSDL2.hpp
        ../includes/display/IDisplayModule.hpp
)

set(GRAPHIC_SDL2_INCLUDE_DIR ../includes/common ../includes/display includes/graphics includes/graphics/SDL2)
target_include_directories(graphic_sdl2 PUBLIC ${GRAPHIC_SDL2_INCLUDE_DIR})
set_target_properties(graphic_sdl2 PROPERTIES OUTPUT_NAME "arcade_sdl2" PREFIX "")
find_package(SDL2 REQUIRED)
target_link_libraries(graphic_sdl2 SDL2 SDL2_image)

# SFML
add_library(graphic_sfml SHARED
        ../src/common/AEntity.cpp
        ../src/common/AEvent.cpp
        ../src/common/AException.cpp
        src/graphics/AGraphic.cpp
        src/graphics/SFML/GraphicSFML.cpp
        ../includes/common/AEntity.hpp
        ../includes/common/AEvent.hpp
        ../includes/common/AException.hpp
        includes/graphics/AGraphic.hpp
        includes/graphics/SFML/GraphicSFML.hpp
        ../includes/display/IDisplayModule.hpp
)

set(GRAPHIC_SFML_INCLUDE_DIR ../includes/common ../includes/display includes/graphics includes/graphics/SFML)
target_include_directories(graphic_sfml PUBLIC ${GRAPHIC_SFML_INCLUDE_DIR})
set_target_properties(graphic_sfml PROPERTIES OUTPUT_NAME "arcade_sfml" PREFIX "")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(graphic_sfml sfml-graphics sfml-window sfml-system)