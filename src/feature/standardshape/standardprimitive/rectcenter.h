#ifndef __RECTCENTER_H__
#define __RECTCENTER_H__

#include "standardprimitive.h"


class RectCenter : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  qreal m_width;
  qreal m_height;
};

#endif
