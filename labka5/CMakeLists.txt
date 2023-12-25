cmake_minimum_required(VERSION 3.23)
project(labka5)

set(CMAKE_CXX_STANDARD 23)

add_executable(labka5 main.cpp Stack.h Clock.cpp Clock.h ElectronicWatch.h ElectronicWatch.cpp FitnessTracker.cpp FitnessTracker.h MechanicClock.cpp MechanicClock.h WallClock.cpp WallClock.h Watch.cpp Watch.h Exception.h Exception.cpp File.h Serializable.h)
