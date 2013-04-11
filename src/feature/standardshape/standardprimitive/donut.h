#ifndef __DONUT_H__
#define __DONUT_H__

#include "standardprimitive.h"
#include "utils.h"
#include "length.h"

class Donut : public StandardPrimitive
{
public:
  Donut() {}
  Donut(Shape s, Length od, Length id) :
      m_shape(s), m_outerDiameter(od), m_innerDiameter(id) {}
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Shape m_shape;
  Length m_outerDiameter;
  Length m_innerDiameter;
};

#endif
