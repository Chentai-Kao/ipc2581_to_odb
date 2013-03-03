TEMPLATE = app

MOC_DIR = .build
UI_DIR = .build
RCC_DIR = .build
OBJECTS_DIR = .build
BUILD_DIR = .build

HEADERS +=

SOURCES += \
  main.cpp

INCLUDEPATH += . .build

DESTDIR = ../bin
TARGET = ipc2581
