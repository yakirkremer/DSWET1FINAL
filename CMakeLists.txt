cmake_minimum_required(VERSION 2.8)
project(DSWET1NOSHARED)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSWET1NOSHARED main.cpp AvlTreeNew.h DbObj.h DbObj.cpp Movie.h Movie.cpp User.cpp User.h GenreMoviesTree.h MoviesTree.h Group.h StreamingDBa1.h StreamingDBa1.cpp maina1.cpp)
