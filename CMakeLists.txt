cmake_minimum_required(VERSION 3.27)
project(rayCastingMaze C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(SDL2 REQUIRED COMPONENTS SDL2)
add_executable(rayCastingMaze
        main.c
        Map/Map.h
        Map/Map.c
        Player/Player.h
        Player/Player.c
        Utils/Vec3/Vec3.h
        Utils/Vec3/Vec3.c
        Utils/Collision/Collision.h
        Utils/Collision/Collision.c
        Utils/RayCaster/RayCaster.h
        Utils/RayCaster/RayCaster.c
        Utils/Stack/Stack.h
        Utils/Stack/Stack.c
        Utils/MazeGenerator/MazeGenerator.h
        Utils/MazeGenerator/MazeGenerator.c
        Utils/ErrorHandler/ErrorHandler.c
        Utils/ErrorHandler/ErrorHandler.h
        Utils/Comparator/Comparator.c
        Utils/Comparator/Comparator.h)
target_link_libraries(rayCastingMaze PRIVATE SDL2::SDL2)
