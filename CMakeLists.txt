cmake_minimum_required(VERSION 3.17)
project(biblioapp)

set(CMAKE_CXX_STANDARD 14)

add_executable(biblioapp main.cpp Personne.cpp Personne.h Livre.cpp Livre.h Etudiant.cpp Etudiant.h
        utils.h
        utils.cpp)