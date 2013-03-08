#ifndef __SPCONTOUR_H__
#define __SPCONTOUR_H__

#include "standardprimitive.h"
#include "spcontourpolygon.h"

class SpContour : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  SpContourPolygon polygonGen(QXmlStreamReader& xml, QString elementName);
  bool isClosedShape(const SpContourPolygon& polygon);

  SpContourPolygon m_polygon;
  QList<SpContourPolygon> m_cutout;
};

#endif
