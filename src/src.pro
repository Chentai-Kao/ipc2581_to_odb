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
  caddatahandler.h \
  cadheaderhandler.h \
  contenthandler.h \
  dictionarycolorhandler.h \
  dictionarylinedeschandler.h \
  dictionarystandardhandler.h \
  dictionaryuserhandler.h \
  drilltool.h \
  ecadhandler.h \
  featurefactory.h \
  feature.h \
  handler.h \
  historyrecordhandler.h \
  layer.h \
  logisticheaderhandler.h \
  settings.h \
  span.h \
  stackupgroup.h \
  stackup.h \
  stackupimpedance.h \
  stackuplayer.h \
  standardprimitivefactory.h \
  toplevelfactory.h \
  toplevelhandler.h \
  userprimitivefactory.h \
  utils.h \
  xform.h

SOURCES += \
  avlhandler.cpp \
  bomhandler.cpp \
  caddatahandler.cpp \
  cadheaderhandler.cpp \
  contenthandler.cpp \
  dictionarycolorhandler.cpp \
  dictionarylinedeschandler.cpp \
  dictionarystandardhandler.cpp \
  dictionaryuserhandler.cpp \
  drilltool.cpp \
  ecadhandler.cpp \
  featurefactory.cpp \
  historyrecordhandler.cpp \
  layer.cpp \
  logisticheaderhandler.cpp \
  main.cpp \
  span.cpp \
  stackup.cpp \
  stackupgroup.cpp \
  stackupimpedance.cpp \
  stackuplayer.cpp \
  standardprimitivefactory.cpp \
  toplevelfactory.cpp \
  toplevelhandler.cpp \
  userprimitivefactory.cpp \
  utils.cpp \
  xform.cpp

INCLUDEPATH += . .build linedescgroup polystep standardprimitive userprimitive color

DESTDIR = ../bin
TARGET = ipc2581
