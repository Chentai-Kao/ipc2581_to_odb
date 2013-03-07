#ifndef __SPOCTAGON_H__
#define __SPOCTAGON_H__

#include "standardprimitive.h"

class SpOctagon : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_length;
};

#endif
