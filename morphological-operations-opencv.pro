######################################################################
# Automatically generated by qmake (3.1) Fri May 21 02:23:56 2021
######################################################################

TEMPLATE = app
TARGET = morphological-operations-opencv
INCLUDEPATH += .
QT += gui widgets

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += header_files/header.hpp
SOURCES += source_files/main-image-gui.cpp \
           source_files/main.cpp \
           source_files/morphological-operation.cpp

INCLUDEPATH += /home/ezhizhpon/Apps/opencv_i-4.5.2/include/opencv4

LIBS += -L/home/ezhizhpon/Apps/opencv_i-4.5.2/lib/ \
		-lopencv_core \
		-lopencv_highgui \
		-lopencv_imgproc \
		-lopencv_imgcodecs \
		-lopencv_video  \
		-lopencv_videoio

OBJECTS_DIR   = ./bin/

DESTDIR       = ./bin/