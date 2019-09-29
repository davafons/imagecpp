cmake_minimum_required(VERSION 3.7.0)

project(img_viz)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

add_executable(${PROJECT_NAME}
    res/res.qrc
    src/main.cpp
    src/mainwindow.cpp
    src/image/imagedisplayarea.cpp
    src/image/proimage.cpp
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts)
