#ifndef __RECTROUND_H__
#define __RECTROUND_H__

#include "standardprimitive.h"
#include "length.h"

class RectRound : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Length m_width;
  Length m_height;
  Length m_radius;
  bool  m_upperRight;
  bool  m_upperLeft;
  bool  m_lowerLeft;
  bool  m_lowerRight;
};

#endif
