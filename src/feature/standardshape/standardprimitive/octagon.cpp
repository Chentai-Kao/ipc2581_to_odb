#include "octagon.h"
#include "contour.h"

void
Octagon::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_length = Length(
      getNonNegativeDoubleAttribute(xml, "Octagon", "length"), units);
}

void
Octagon::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  Contour surface;
  QPointF p(0, 0.5 * m_length.inch());
  surface.polygon().setPolyBegin(p);
  for (int i = 0; i < 8; ++i) {
    p = rotatePoint(p, 45);
    surface.polygon().addSegment(p);
  }
  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
