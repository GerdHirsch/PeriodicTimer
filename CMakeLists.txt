cmake_minimum_required(VERSION 3.12)
project(TrafficControlSystem)

# Configure Compiler flags
set(CMAKE_CXX_STANDARD 17)
if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}"
                                                     STREQUAL "GNU")
)# using GCC or CLang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic") # -Werror
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC") # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()

# Add subdirs
add_subdirectory(SimplePeriodicTimer)
add_subdirectory(PeriodicTimerCUTE)
