#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "standardprimitive.h"

class Triangle : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_base;
  qreal m_height;
};

#endif
