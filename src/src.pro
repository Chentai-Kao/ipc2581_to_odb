TEMPLATE = app

MOC_DIR = .build
UI_DIR = .build
RCC_DIR = .build
OBJECTS_DIR = .build
BUILD_DIR = .build

include (attribute/attribute.pri)
include (colorgroup/colorgroup.pri)
include (feature/feature.pri)
include (fiducial/fiducial.pri)
include (linedescgroup/linedescgroup.pri)
include (polystep/polystep.pri)

HEADERS += \
  avlhandler.h \
  bomhandler.h \
  caddatahandler.h \
  cadheaderhandler.h \
  component.h \
  contenthandler.h \
  dictionarycolorhandler.h \
  dictionarylinedeschandler.h \
  dictionarystandardhandler.h \
  dictionaryuserhandler.h \
  drilltool.h \
  ecadhandler.h \
  error.h \
  featuresgroup.h \
  globals.h \
  handler.h \
  historyrecordhandler.h \
  hole.h \
  landpattern.h \
  layerfeature.h \
  layer.h \
  length.h \
  logicalnet.h \
  logisticheaderhandler.h \
  odb.h \
  odbfeaturefile.h \
  odbcomponentfile.h \
  package.h \
  pad.h \
  phynetgroup.h \
  phynet.h \
  phynetpoint.h \
  pinref.h \
  set.h \
  slot.h \
  span.h \
  stackupgroup.h \
  stackup.h \
  stackupimpedance.h \
  stackuplayer.h \
  standardfont.h \
  step.h \
  steprepeat.h \
  target.h \
  toplevelhandler.h \
  utils.h \
  xform.h

SOURCES += \
  avlhandler.cpp \
  bomhandler.cpp \
  caddatahandler.cpp \
  cadheaderhandler.cpp \
  component.cpp \
  contenthandler.cpp \
  dictionarycolorhandler.cpp \
  dictionarylinedeschandler.cpp \
  dictionarystandardhandler.cpp \
  dictionaryuserhandler.cpp \
  drilltool.cpp \
  ecadhandler.cpp \
  featuresgroup.cpp \
  globals.cpp \
  historyrecordhandler.cpp \
  hole.cpp \
  landpattern.cpp \
  layer.cpp \
  layerfeature.cpp \
  logicalnet.cpp \
  logisticheaderhandler.cpp \
  main.cpp \
  odb.cpp \
  package.cpp \
  pad.cpp \
  phynet.cpp \
  phynetgroup.cpp \
  phynetpoint.cpp \
  pinref.cpp \
  set.cpp \
  slot.cpp \
  span.cpp \
  stackup.cpp \
  stackupgroup.cpp \
  stackupimpedance.cpp \
  stackuplayer.cpp \
  step.cpp \
  steprepeat.cpp \
  target.cpp \
  toplevelhandler.cpp \
  utils.cpp \
  xform.cpp

INCLUDEPATH += . .build attribute colorgroup feature fiducial linedescgroup polystep

CONFIG += release
CONFIG += console

DESTDIR = ../bin
TARGET = ipc2581
