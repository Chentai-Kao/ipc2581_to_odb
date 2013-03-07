#ifndef __SPRECTCORNER_H__
#define __SPRECTCORNER_H__

#include "standardprimitive.h"

class SpRectCorner : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_lowerLeftX;
  qreal m_lowerLeftY;
  qreal m_upperRightX;
  qreal m_upperRightY;
};

#endif
