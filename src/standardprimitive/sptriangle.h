#ifndef __SPTRIANGLE_H__
#define __SPTRIANGLE_H__

#include "standardprimitive.h"

class SpTriangle : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_base;
  qreal m_height;
};

#endif
