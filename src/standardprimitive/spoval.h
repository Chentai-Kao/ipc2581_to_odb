#ifndef __SPOVAL_H__
#define __SPOVAL_H__

#include "standardprimitive.h"

class SpOval : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_width;
  qreal m_height;
};

#endif
