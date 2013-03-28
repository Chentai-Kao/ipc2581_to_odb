#ifndef __TEXT_H__
#define __TEXT_H__

#include <QtCore>
#include "utils.h"
#include "userprimitive.h"
#include "error.h"

class Text : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  virtual void odbOutputLayerFeature(
      QList<QString>& symbolsTable,
      QList<QString>& attributeTable,
      QList<QString>& attributeTexts,
      QList<QString>& featuresList,
      QString polarity,
      QPointF location, Xform *xform);
};

#endif
