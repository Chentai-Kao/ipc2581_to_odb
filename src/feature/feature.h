#ifndef __FEATURE_H__
#define __FEATURE_H__

#include <QtCore>
#include "utils.h"

// Base class of "feature":
// StandardShape, UserShape
class Feature
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
  virtual QString refId() = 0; // by StandardPrimitiveRef and UserPrimitiveRef
  virtual void odbOutputLayerFeature(
      QList<QString>& symbolsTable,
      QList<QString>& attributeTable,
      QList<QString>& attributeTexts,
      QList<QString>& featuresList,
      QString polarity,
      QPointF location, Xform *xform) = 0;
};

#endif
