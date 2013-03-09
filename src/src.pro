TEMPLATE = app

MOC_DIR = .build
UI_DIR = .build
RCC_DIR = .build
OBJECTS_DIR = .build
BUILD_DIR = .build

include (standardprimitive/standardprimitive.pri)
include (userprimitive/userprimitive.pri)
include (linedescgroup/linedescgroup.pri)
include (polystep/polystep.pri)
include (color/color.pri)

HEADERS += \
  avlhandler.h \
  bomhandler.h \
  contenthandler.h \
  ecadhandler.h \
  feature.h \
  featurefactory.h \
  handler.h \
  historyrecordhandler.h \
  logisticheaderhandler.h \
  settings.h \
  standardprimitivefactory.h \
  dictionarycolorhandler.h \
  dictionarylinedeschandler.h \
  dictionarystandardhandler.h \
  dictionaryuserhandler.h \
  toplevelfactory.h \
  toplevelhandler.h \
  userprimitivefactory.h \
  utils.h \

SOURCES += \
  main.cpp \
  avlhandler.cpp \
  bomhandler.cpp \
  contenthandler.cpp \
  ecadhandler.cpp \
  featurefactory.cpp \
  historyrecordhandler.cpp \
  logisticheaderhandler.cpp \
  standardprimitivefactory.cpp \
  dictionarycolorhandler.cpp \
  dictionarylinedeschandler.cpp \
  dictionarystandardhandler.cpp \
  dictionaryuserhandler.cpp \
  toplevelfactory.cpp \
  toplevelhandler.cpp \
  userprimitivefactory.cpp \
  utils.cpp

INCLUDEPATH += . .build linedescgroup polystep standardprimitive userprimitive color

DESTDIR = ../bin
TARGET = ipc2581
