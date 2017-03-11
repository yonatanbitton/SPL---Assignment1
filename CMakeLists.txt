cmake_minimum_required(VERSION 3.6)
project(ass1_Reviiyot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/Card.h
        include/Deck.h
        include/Game.h
        include/Hand.h
        include/Player.h
        src/Card.cpp
        src/Deck.cpp
        src/Game.cpp
        src/Hand.cpp
        src/Player.cpp
        src/reviiyot.cpp)

add_executable(ass1_Reviiyot ${SOURCE_FILES})