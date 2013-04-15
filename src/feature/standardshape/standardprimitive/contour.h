#ifndef __CONTOUR_H__
#define __CONTOUR_H__

#include "standardprimitive.h"
#include "polygon.h"
#include "length.h"

class Contour : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);
  void addCutout() {
    Polygon c;
    m_cutouts.append(c);
  }
  void clear() {
    m_polygon.clear();
    m_cutouts.clear();
  }

  // getter
  Polygon& polygon() { return m_polygon; }
  Polygon& cutout() { return m_cutouts.last(); }

private:
  Polygon m_polygon;
  QList<Polygon> m_cutouts;
};

#endif
