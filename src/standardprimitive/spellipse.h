#ifndef __SPELLIPSE_H__
#define __SPELLIPSE_H__

#include "standardprimitive.h"

class SpEllipse : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_width;
  qreal m_height;
};

#endif
