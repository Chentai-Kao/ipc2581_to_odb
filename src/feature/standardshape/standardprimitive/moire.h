#ifndef __MOIRE_H__
#define __MOIRE_H__

#include "standardprimitive.h"


class Moire : public StandardPrimitive
{
public:
  Moire() : m_lineWidth(0), m_lineLength(0), m_lineAngle(0) {}
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

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
