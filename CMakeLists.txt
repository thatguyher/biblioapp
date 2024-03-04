cmake_minimum_required(VERSION 3.17)
project(biblioapp)

set(CMAKE_CXX_STANDARD 14)

add_executable(biblioapp main.cpp Personnage.cpp Personnage.h Personne.cpp Personne.h)