cmake_minimum_required(VERSION 3.7)
project(Final)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)


add_executable(Final main.cpp mainwindow.cpp mainwindow.h mainscene.h mainscene.cpp prism.cpp prism.h )

target_link_libraries(Final Qt5::Widgets Qt5::Multimedia)