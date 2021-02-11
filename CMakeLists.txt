cmake_minimum_required(VERSION 3.13)
project(SFMLPong)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system")

add_executable(SFMLPong main.cpp bat.h bat.cpp ball.cpp ball.h)
