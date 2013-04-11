#ifndef __RECTCHAM_H__
#define __RECTCHAM_H__

#include "standardprimitive.h"
#include "length.h"

class RectCham : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Length m_width;
  Length m_height;
  Length m_chamfer;
  bool  m_upperRight;
  bool  m_upperLeft;
  bool  m_lowerLeft;
  bool  m_lowerRight;
};

#endif
