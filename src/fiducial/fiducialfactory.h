#ifndef __FIDUCIALFACTORY_H__
#define __FIDUCIALFACTORY_H__

#include <QtCore>
#include "fiducial.h"

class FiducialFactory
{
public:
  Fiducial* create(QStringRef elementName);
};

#endif
