#include "oval.h"
#include "error.h"
#include "contour.h"

void
Oval::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_width = Length(
      getNonNegativeDoubleAttribute(xml, "Oval", "width"), units);
  m_height = Length(
      getNonNegativeDoubleAttribute(xml, "Oval", "height"), units);
  if (m_height.mil() > m_width.mil()) {
    throw new InvalidAttributeError("Oval", "height");
  }
}

void
Oval::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  qreal w = m_width.inch(),
        h = m_height.inch();
  QPointF p1( 0.5 * (w - h),  0.5 * h),
          p2(-0.5 * (w - h),  0.5 * h),
          p3(-0.5 * (w - h), -0.5 * h),
          p4( 0.5 * (w - h), -0.5 * h);
  Contour surface;
  surface.polygon().setPolyBegin(p1);
  surface.polygon().addSegment(p2);
  surface.polygon().addCurve(p3, QPointF(-0.5 * (w - h), 0), false);
  surface.polygon().addSegment(p4);
  surface.polygon().addCurve(p1, QPointF(0.5 * (w - h), 0), false);
  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
