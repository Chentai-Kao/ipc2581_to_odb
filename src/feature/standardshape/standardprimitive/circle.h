#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "standardprimitive.h"

class Circle : public StandardPrimitive
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

private:
  qreal m_diameter;
};

#endif
