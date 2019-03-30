#-------------------------------------------------
#
# Project created by QtCreator 2019-03-29T21:25:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Part_2
TEMPLATE = app

unix:!mac {
    message("* Using settings for Unix/Linux.")
    INCLUDEPATH += /usr/local/include/opencv
    INCLUDEPATH += $$PWD/../eigen-eigen-323c052e1731/Eigen
    LIBS += -L/usr/local/lib/ \
        -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc
}
## OpenCV settings for Mac OS X
macx {
    message("* Using settings for Mac OS X.")
    INCLUDEPATH += /usr/local/include/opencv
     INCLUDEPATH += $$PWD/../eigen-eigen-323c052e1731/Eigen
    LIBS += -L/usr/local/lib/ \
        -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc
}

## OpenCV settings for Windows and OpenCV 2.4.2
win32 {
    message("* Using settings for Windows.")
    INCLUDEPATH += "C:\\opencv\\build\\include" \
                   "C:\\opencv\\build\\include\\opencv" \
                   "C:\\opencv\\build\\include\\opencv2"

    INCLUDEPATH += $$PWD/../eigen-eigen-323c052e1731/Eigen

    CONFIG(debug, debug | release) {
        LIBS += -L"C:\\opencv\\build\\x86\\vc10\\lib" \
            -lopencv_core248d \
            -lopencv_highgui248d \
            -lopencv_imgproc248d
    }

    CONFIG(release, debug | release) {
        LIBS += -L"C:\\opencv\\build\\x86\\vc10\\lib" \
            -lopencv_core248 \
            -lopencv_highgui248 \
            -lopencv_imgproc248
    }
}

# Runs this app automatically after the building has succeeded
#QMAKE_POST_LINK=./$$TARGET

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        part2.cpp

HEADERS += \
        part2.h

FORMS += \
        part2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


