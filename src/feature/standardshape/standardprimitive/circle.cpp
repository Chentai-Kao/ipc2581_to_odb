#include "circle.h"
#include "contour.h"

void
Circle::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_diameter = Length(
      getNonNegativeDoubleAttribute(xml, "Circle", "diameter"), units);
}

void
Circle::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  qreal r = m_diameter.inch();

  Contour surface;
  surface.polygon().setPolyBegin(QPointF(0, 0.5 * r));
  surface.polygon().addCurve(QPointF(0, 0.5 * r), QPointF(0, 0), false);
  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
