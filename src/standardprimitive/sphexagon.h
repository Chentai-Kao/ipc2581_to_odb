#ifndef __SPHEXAGON_H__
#define __SPHEXAGON_H__

#include "standardprimitive.h"

class SpHexagon : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_length;
};

#endif
