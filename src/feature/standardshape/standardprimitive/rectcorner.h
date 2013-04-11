#ifndef __RECTCORNER_H__
#define __RECTCORNER_H__

#include "standardprimitive.h"
#include "length.h"

class RectCorner : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Length m_lowerLeftX;
  Length m_lowerLeftY;
  Length m_upperRightX;
  Length m_upperRightY;
};

#endif
