#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T08:44:05
#
#-------------------------------------------------
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ParsePlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    plotdata.cpp \
    plotpressure.cpp \
    plotaccel.cpp \
    plotdigdata.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    plotdata.h \
    Common/IfsDefs.h \
    plotpressure.h \
    plotaccel.h \
    Common/DigDefs.h \
    plotdigdata.h \
    Common/FireFlyDefsOld.h \
    Common/gpsdCommonOld.h

FORMS    += mainwindow.ui \
    graph.ui \
    plotdata.ui \
    plotpressure.ui \
    plotaccel.ui \
    plotdigdata.ui
