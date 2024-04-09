cmake_minimum_required(VERSION 3.17)

set(NAME arcade)

project(${NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CORE_SRC
        src/common/AEntity.cpp
        src/common/AEvent.cpp
        src/common/AException.cpp
        src/Core.cpp
        src/DLManager.cpp
        src/main.cpp
        includes/common/AEntity.hpp
        includes/common/AEvent.hpp
        includes/common/AException.hpp
        includes/Core.hpp
        includes/DLManager.hpp
        includes/game/IGameModule.hpp
        includes/display/IDisplayModule.hpp
)

add_compile_options(-W -Wall -Wextra -Werror -fno-gnu-unique)
set(INCLUDE_DIR includes includes/display includes/game includes/common)

add_executable(${NAME} ${CORE_SRC})
target_link_libraries(${NAME} PUBLIC dl)
target_include_directories(${NAME} PUBLIC ${INCLUDE_DIR})

add_subdirectory(lib)