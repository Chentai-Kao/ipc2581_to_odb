#ifndef __SPMOIRE_H__
#define __SPMOIRE_H__

#include "standardprimitive.h"

class SpMoire : public StandardPrimitive
{
public:
  SpMoire() : m_lineWidth(0), m_lineLength(0), m_lineAngle(0) {}
  virtual void initialize(QXmlStreamReader& xml);

private:
  // required attributes
  qreal m_diameter;
  qreal m_ringWidth;
  qreal m_ringGap;
  int   m_ringNumber;
  // optional attributes
  qreal m_lineWidth;
  qreal m_lineLength;
  qreal m_lineAngle;
};

#endif
