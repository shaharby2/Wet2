cmake_minimum_required(VERSION 3.23)
project(Wet2_new)

set(CMAKE_CXX_STANDARD 11)

add_executable(Wet2_new
        worldcup23a2.cpp
        worldcup23a2.h
        wet2util.h
        AVL.h
        Node.h
        player.cpp
        player.h
        team.h
        team.cpp
        chain_Node.h
        hash_table.h
        hash_table.cpp
        Union_Find.h
        Union_Find.cpp
        main23a2.cpp)
