#ifndef __BUTTERFLY_H__
#define __BUTTERFLY_H__

#include "standardprimitive.h"

class Butterfly : public StandardPrimitive
{
public:
  enum ButterflyShape {
    ROUND,
    SQUARE
  };
  virtual void initialize(QXmlStreamReader& xml);

private:
  ButterflyShape m_shape;
  qreal m_diameter; // for ROUND butterfly
  qreal m_side; // for SQUARE butterfly
};

#endif
