QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

# Указываем исходные файлы
SOURCES += \
    tst_laba2.cpp \
     ../app/naturalnum.cpp

# Указываем пути к заголовочным файлам
HEADERS += \
    ../app/naturalnum.h

# Указываем путь к директории, где нужно искать заголовочные файлы
INCLUDEPATH += ../app

TARGET = laba2Tests
