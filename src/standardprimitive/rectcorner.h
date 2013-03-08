#ifndef __RECTCORNER_H__
#define __RECTCORNER_H__

#include "standardprimitive.h"

class RectCorner : public StandardPrimitive
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
