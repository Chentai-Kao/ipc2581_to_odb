#ifndef __RECTCENTER_H__
#define __RECTCENTER_H__

#include "standardprimitive.h"
#include "length.h"

class RectCenter : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Length m_width;
  Length m_height;
};

#endif
