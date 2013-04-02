#ifndef __CONTOUR_H__
#define __CONTOUR_H__

#include "standardprimitive.h"
#include "polygon.h"


class Contour : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  Polygon m_polygon;
  QList<Polygon> m_cutouts;
};

#endif
