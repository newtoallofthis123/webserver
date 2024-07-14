cmake_minimum_required(VERSION 3.28)
project(webserver)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(webserver
    src/main.cpp
        src/server.h
        src/server.cpp
        src/http.cpp
        src/http.h
        src/fs.h
        src/fs.cpp
)

target_link_libraries(webserver pthread)