#include "rectcenter.h"
#include "contour.h"

void
RectCenter::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_width = Length(
      getNonNegativeDoubleAttribute(xml, "RectCenter", "width"), units);
  m_height = Length(
      getNonNegativeDoubleAttribute(xml, "RectCenter", "height"), units);
}

void
RectCenter::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  qreal w = m_width.inch(),
        h = m_height.inch();

  Contour surface;
  surface.polygon().setPolyBegin(QPointF(0.5 * w,  0.5 * h));
  surface.polygon().addSegment(QPointF( -0.5 * w,  0.5 * h));
  surface.polygon().addSegment(QPointF( -0.5 * w, -0.5 * h));
  surface.polygon().addSegment(QPointF(  0.5 * w, -0.5 * h));
  surface.polygon().addSegment(QPointF(  0.5 * w,  0.5 * h));
  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
