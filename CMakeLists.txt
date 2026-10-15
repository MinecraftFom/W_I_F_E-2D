cmake_minimum_required(VERSION 3.28.3)
project(WIFE2d)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "~/libs/qt/6.12.0/gcc_64/lib/cmake/Qt6")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(GLOB C_SOURCES "./src/*.c")
file(GLOB CPP_SOURCES "./src/*.cpp")
include_directories("./includes")
add_executable(WIFE2d ${C_SOURCES} ${CPP_SOURCES})
target_link_libraries(WIFE2d
        Qt::Core
        Qt::Gui
        Qt::Widgets
)