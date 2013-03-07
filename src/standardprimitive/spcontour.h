#ifndef __SPCONTOUR_H__
#define __SPCONTOUR_H__

#include "standardprimitive.h"
#include "spcontourpolygonorcontour.h"

class SpContour : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  SpContourPolygonOrCutout m_polygon;
  QList<SpContourPolygonOrCutout> m_cutout;
};

#endif
