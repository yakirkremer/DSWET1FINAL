cmake_minimum_required(VERSION 3.22.1)
project(DSWET1NOSHARED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS " -std=c++11 -DNDEBUG -Wall")
add_executable(DSWET1NOSHARED main.cpp AvlTreeNew.h DbObj.h DbObj.cpp Movie.h Movie.cpp User.cpp User.h GenreMoviesTree.h MoviesTree.h Group.h StreamingDBa1.h StreamingDBa1.cpp maina1.cpp GroupsTree.h)

