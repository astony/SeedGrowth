#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T11:28:25
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeedGrowth
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES     += main.cpp \
               gui.cpp \
    general_tab.cpp \
    options_tab.cpp \
    tab_widget.cpp \
    image_widget.cpp \
    generator/base.cpp \
    generator/random.cpp \
    generator/random_with_radius.cpp \
    generator/regular.cpp


HEADERS     += \
               gui.hpp \
    general_tab.hpp \
    options_tab.hpp \
    tab_widget.hpp \
    image_widget.hpp \
    generator/base.hpp \
    generator/random.hpp \
    generator/random_with_radius.hpp \
    generator/regular.hpp

