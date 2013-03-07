#ifndef __SPDIAMOND_H__
#define __SPDIAMOND_H__

#include "standardprimitive.h"

class SpDiamond : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_width;
  qreal m_height;
};

#endif
