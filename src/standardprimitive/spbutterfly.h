#ifndef __SPBUTTERFLY_H__
#define __SPBUTTERFLY_H__

#include "standardprimitive.h"

class SpButterfly : public StandardPrimitive
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
