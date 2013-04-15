#include "hexagon.h"
#include "contour.h"

void
Hexagon::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_length = Length(
      getNonNegativeDoubleAttribute(xml, "Hexagon", "length"), units);
}

void
Hexagon::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  Contour surface;
  QPointF p(0, 0.5 * m_length.inch());
  surface.polygon().setPolyBegin(p);
  for (int i = 0; i < 6; ++i) {
    p = rotatePoint(p, 60);
    surface.polygon().addSegment(p);
  }
  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
