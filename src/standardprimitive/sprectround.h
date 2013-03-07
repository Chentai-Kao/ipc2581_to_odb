#ifndef __SPRECTROUND_H__
#define __SPRECTROUND_H__

#include "standardprimitive.h"

class SpRectRound : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_width;
  qreal m_height;
  qreal m_radius;
  bool  m_upperRight;
  bool  m_upperLeft;
  bool  m_lowerLeft;
  bool  m_lowerRight;
};

#endif
