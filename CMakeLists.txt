cmake_minimum_required(VERSION 3.7.0)

project(imagecpp)

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
    src/image/document.cpp
    src/image/histogram.cpp
    src/image/histogramchannel.cpp
    src/image/image.cpp
    src/image/histogramview.cpp
    src/operations/grayscale/grayscale.cpp
    src/operations/grayscale/grayscaledialog.cpp
    src/operations/difference/imagedifference.cpp
    src/operations/change/imagechangedialog.cpp
    src/operations/filter/filter.cpp
    src/operations/filter/filterdialog.cpp
    src/operations/change/imagechange.cpp
    src/operations/difference/imagedifferencedialog.cpp
    src/operations/inverse/inverse.cpp
    src/operations/equalization/equalization.cpp
    src/operations/specification/specification.cpp
    src/operations/specification/specificationdialog.cpp
    src/operations/transform/lineartransform.cpp
    src/operations/transform/lineartransformdialog.cpp
    src/operations/bac/bac.cpp
    src/operations/digitalization/digitalization.cpp
    src/operations/digitalization/digitalizationdialog.cpp
    src/operations/bac/bacdialog.cpp
    src/operations/private/pointoperation.cpp
    src/operations/private/filteroperation.cpp
    src/operations/gammac/gammac.cpp
    src/operations/gammac/gammacdialog.cpp
    src/operations/mirror/mirror.cpp
    src/operations/mirror/transpose.cpp
    src/operations/private/imageoperation.cpp
    src/operations/private/lutoperation.cpp
    src/operations/rotation/rotation.cpp
    src/operations/rotation/rotationdialog.cpp
    src/widgets/image/imagedisplayarea.cpp
    src/widgets/image/imagesubwindow.cpp
    src/widgets/image/imageslistwidget.cpp
    src/widgets/menus/filemenu.cpp
    src/widgets/menus/imagemenu.cpp
    src/widgets/menus/editmenu.cpp
    src/widgets/menus/windowsmenu.cpp
    src/widgets/menus/settingsmenu.cpp
    src/widgets/menus/mainmenubar.cpp
    src/widgets/dock/resizabledockwidget.cpp
    src/widgets/statusbar/mainstatusbar.cpp
    src/widgets/statusbar/pixelinformationwidget.cpp
    src/widgets/image/subwindowsarea.cpp
    src/widgets/utils/sliderwithvalues.cpp
    src/manager/documentsmanager.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src/)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts)
