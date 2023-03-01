cmake_minimum_required(VERSION 3.0.0)
project(uniform-grid VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)

file(GLOB_RECURSE HEADERS "include/*.hpp")
file(GLOB SOURCES "src/*.cpp")

include_directories("include")
add_executable(uniform-grid ${SOURCES} ${HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(uniform-grid PRIVATE SDL2::SDL2)
