#ifndef __SPRECTCHAM_H__
#define __SPRECTCHAM_H__

#include "standardprimitive.h"

class SpRectCham : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_width;
  qreal m_height;
  qreal m_chamfer;
  bool  m_upperRight;
  bool  m_upperLeft;
  bool  m_lowerLeft;
  bool  m_lowerRight;
};

#endif
