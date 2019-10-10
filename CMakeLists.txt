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
    src/image/imagedata.cpp
    src/image/proimage.cpp
    src/operations/tograyscale.cpp
    src/operations/private/imageoperation.cpp
    src/widgets/image/imagedisplayarea.cpp
    src/widgets/image/imagesubwindow.cpp
    src/widgets/menus/filemenu.cpp
    src/widgets/menus/imagemenu.cpp
    src/widgets/menus/editmenu.cpp
    src/widgets/menus/windowsmenu.cpp
    src/widgets/menus/settingsmenu.cpp
    src/widgets/menus/mainmenubar.cpp
    src/widgets/statusbar/mainstatusbar.cpp
    src/widgets/statusbar/pixelinformationwidget.cpp
    src/widgets/image/subwindowsarea.cpp
    src/manager/imagemanager.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src/)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts)
