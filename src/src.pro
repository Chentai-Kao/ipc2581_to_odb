TEMPLATE = app

MOC_DIR = .build
UI_DIR = .build
RCC_DIR = .build
OBJECTS_DIR = .build
BUILD_DIR = .build

include (standardprimitive/standardprimitive.pri)

HEADERS += \
  avlhandler.h \
  bomhandler.h \
  contenthandler.h \
  ecadhandler.h \
  handler.h \
  historyrecordhandler.h \
  logisticheaderhandler.h \
  settings.h \
  standardprimitivefactory.h \
  dictionarystandardhandler.h \
  toplevelfactory.h \
  toplevelhandler.h \
  utils.h \

SOURCES += \
  main.cpp \
  avlhandler.cpp \
  bomhandler.cpp \
  contenthandler.cpp \
  ecadhandler.cpp \
  historyrecordhandler.cpp \
  logisticheaderhandler.cpp \
  standardprimitivefactory.cpp \
  dictionarystandardhandler.cpp \
  toplevelfactory.cpp \
  toplevelhandler.cpp \
  utils.cpp

INCLUDEPATH += . .build standardprimitive

DESTDIR = ../bin
TARGET = ipc2581
