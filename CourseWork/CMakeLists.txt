cmake_minimum_required(VERSION 3.23.2)
project(CourseWork)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/libpqxx-7.8.1)
add_executable(CourseWork main.cpp)

target_link_libraries(CourseWork pqxx)
