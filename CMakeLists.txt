cmake_minimum_required(VERSION 3.24)
project(todo_notify)
set(CMAKE_CXX_STANDARD 23)

find_library(libvlc NAMES libvlcpp libvlc libvlccore vlcpp vlc
        PATHS /usr/lib /usr/lib64/ /usr/lib64/vlc)

add_executable(todo_notify src/main.cpp src/include/parser.hpp src/parser.cpp src/include/date.hpp src/date.cpp src/notification.cpp src/include/notification.hpp)
target_link_libraries(todo_notify PRIVATE stdc++fs  ${libvlc})
