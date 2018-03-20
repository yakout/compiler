cmake_minimum_required(VERSION 3.8)
project(java_compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp lexical_analyzer_generator lexical_analyzer)
add_executable(java_compiler ${SOURCE_FILES})

target_link_libraries(java_compiler)
