cmake_minimum_required(VERSION 2.8)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

## Use the variable PROJECT_NAME for changing the target name
set( PROJECT_NAME "random_generator_iterator" )

## Set our project name
project(${PROJECT_NAME})

set(SRCS "main.cpp")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  option(USE_RDRND "enable rdrnd" 1)
  option(USE_RDSEED "enable rdseed" 0)
  if(USE_RDRND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mrdrnd")
  endif()
  if(USE_RDSEED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mrdseed")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

## Define the executable
add_executable(${PROJECT_NAME} ${SRCS})
