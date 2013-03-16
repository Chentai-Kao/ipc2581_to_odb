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
include (attribute/attribute.pri)
include (fiducial/fiducial.pri)

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
  featurefactory.h \
  feature.h \
  handler.h \
  historyrecordhandler.h \
  landpattern.h \
  layer.h \
  logicalnet.h \
  logisticheaderhandler.h \
  package.h \
  pad.h \
  phynetgroup.h \
  phynet.h \
  phynetpoint.h \
  pinref.h \
  settings.h \
  span.h \
  stackupgroup.h \
  stackup.h \
  stackupimpedance.h \
  stackuplayer.h \
  standardprimitivefactory.h \
  standardprimitiveref.h \
  standardshape.h \
  step.h \
  target.h \
  toplevelfactory.h \
  toplevelhandler.h \
  userprimitivefactory.h \
  userprimitiveref.h \
  usershape.h \
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
  featurefactory.cpp \
  historyrecordhandler.cpp \
  landpattern.cpp \
  layer.cpp \
  logicalnet.cpp \
  logisticheaderhandler.cpp \
  main.cpp \
  package.cpp \
  pad.cpp \
  phynet.cpp \
  phynetgroup.cpp \
  phynetpoint.cpp \
  pinref.cpp \
  span.cpp \
  stackup.cpp \
  stackupgroup.cpp \
  stackupimpedance.cpp \
  stackuplayer.cpp \
  standardprimitivefactory.cpp \
  standardprimitiveref.cpp \
  step.cpp \
  target.cpp \
  toplevelfactory.cpp \
  toplevelhandler.cpp \
  userprimitivefactory.cpp \
  userprimitiveref.cpp \
  utils.cpp \
  xform.cpp

INCLUDEPATH += . .build linedescgroup polystep standardprimitive userprimitive color attribute fiducial

DESTDIR = ../bin
TARGET = ipc2581
