#ifndef __DONUT_H__
#define __DONUT_H__

#include "standardprimitive.h"

class Donut : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  enum DonutShape { ROUND, SQUARE, HEXAGON, OCTAGON } m_shape;
  qreal m_outerDiameter;
  qreal m_innerDiameter;
};

#endif
