#ifndef __HEXAGON_H__
#define __HEXAGON_H__

#include "standardprimitive.h"
#include "length.h"

class Hexagon : public StandardPrimitive
{
public:
  Hexagon() {}
  Hexagon(Length l) : m_length(l) {}
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Length m_length;
};

#endif
