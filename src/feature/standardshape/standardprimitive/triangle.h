#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "standardprimitive.h"
#include "length.h"

class Triangle : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Length m_base;
  Length m_height;
};

#endif
