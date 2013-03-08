#ifndef __CONTOUR_H__
#define __CONTOUR_H__

#include "standardprimitive.h"
#include "contourpolygon.h"

class Contour : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  ContourPolygon polygonGen(QXmlStreamReader& xml, QString elementName);
  bool isClosedShape(const ContourPolygon& polygon);

  ContourPolygon m_polygon;
  QList<ContourPolygon> m_cutout;
};

#endif
