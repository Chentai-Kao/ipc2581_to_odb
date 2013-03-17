include (feature/standardshape/standardshape.pri)
include (feature/usershape/usershape.pri)

HEADERS += \
  feature/featurefactory.h \
  feature/feature.h

SOURCES += \
  feature/featurefactory.cpp

INCLUDEPATH += feature/standardshape/ feature/usershape/
