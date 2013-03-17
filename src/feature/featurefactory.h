#ifndef __FEATUREFACTORY_H__
#define __FEATUREFACTORY_H__

#include <QtCore>
#include "feature.h"

class FeatureFactory
{
public:
  Feature* create(QStringRef elementName);
};

#endif
