#ifndef __OVAL_H__
#define __OVAL_H__

#include "standardprimitive.h"

class Oval : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_width;
  qreal m_height;
};

#endif
