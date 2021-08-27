cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(AAProject1)

# add the MathFunctions library
add_subdirectory(lib)

# add the executable
add_executable(main main.cpp)

target_link_libraries(main PUBLIC NetworkFlowLib)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(main PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib"
                          )