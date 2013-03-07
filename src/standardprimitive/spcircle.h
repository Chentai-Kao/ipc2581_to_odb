#ifndef __SPCIRCLE_H__
#define __SPCIRCLE_H__

#include "standardprimitive.h"

class SpCircle : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_diameter;
};

#endif
