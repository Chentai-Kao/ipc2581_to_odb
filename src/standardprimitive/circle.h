#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "standardprimitive.h"

class Circle : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_diameter;
};

#endif
