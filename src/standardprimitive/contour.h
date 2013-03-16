#ifndef __CONTOUR_H__
#define __CONTOUR_H__

#include "standardprimitive.h"
#include "polygon.h"

class Contour : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  Polygon m_polygon;
  QList<Polygon> m_cutouts;
};

#endif
