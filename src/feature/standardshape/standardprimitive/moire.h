#ifndef __MOIRE_H__
#define __MOIRE_H__

#include "standardprimitive.h"
#include "length.h"

class Moire : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  // required attributes
  Length m_diameter;
  Length m_ringWidth;
  Length m_ringGap;
  int   m_ringNumber;
  // optional attributes
  Length m_lineWidth;
  Length m_lineLength;
  qreal m_lineAngle;
};

#endif
