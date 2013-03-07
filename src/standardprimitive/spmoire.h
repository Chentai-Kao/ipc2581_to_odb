#ifndef __SPMOIRE_H__
#define __SPMOIRE_H__

#include "standardprimitive.h"

class SpMoire : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_diameter;
  qreal m_ringWidth;
  qreal m_ringGap;
  int   m_ringNumber;
  qreal m_lineWidth;
  qreal m_lineLength;
  qreal m_lineAngle;
};

#endif
