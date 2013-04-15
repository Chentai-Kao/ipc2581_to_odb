#include "triangle.h"
#include "contour.h"

void
Triangle::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_base = Length(
      getNonNegativeDoubleAttribute(xml, "Triangle", "base"), units);
  m_height = Length(
      getNonNegativeDoubleAttribute(xml, "Triangle", "height"), units);
}

void
Triangle::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  qreal b = m_base.inch(),
        h = m_height.inch();

  Contour surface;
  surface.polygon().setPolyBegin(QPointF(0, 0.5 * h));
  surface.polygon().addSegment(QPointF(-0.5 * b, -0.5 * h));
  surface.polygon().addSegment(QPointF(0.5 * b, -0.5 * h));
  surface.polygon().addSegment(QPointF(0, 0.5 * h));
  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
