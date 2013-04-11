#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "standardprimitive.h"
#include "length.h"

class Circle : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Length m_diameter;
};

#endif
