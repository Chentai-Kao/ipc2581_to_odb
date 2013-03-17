#ifndef __ELLIPSE_H__
#define __ELLIPSE_H__

#include "standardprimitive.h"

class Ellipse : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_width;
  qreal m_height;
};

#endif
