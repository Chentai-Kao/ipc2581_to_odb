#ifndef __SIMPLE_H__
#define __SIMPLE_H__

#include <QtCore>
#include "utils.h"
#include "userprimitive.h"

// Base class of "Simple":
// Arc, Line, Outline, Polyline
class Simple : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
  virtual void odbOutputLayerFeature(
      QList<QString>& symbolsTable,
      QList<QString>& attributeTable,
      QList<QString>& attributeTexts,
      QList<QString>& featuresList,
      QString polarity,
      QPointF location, Xform *xform) = 0;
};

#endif
