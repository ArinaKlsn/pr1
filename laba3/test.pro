QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS +=  ../app/nod.h
SOURCES +=  tst_nod.cpp ../app/nod.cpp
