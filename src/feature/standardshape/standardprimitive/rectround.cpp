#include "rectround.h"
#include "error.h"
#include "contour.h"

void
RectRound::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_width = Length(
      getNonNegativeDoubleAttribute(xml, "RectRound", "width"), units);
  m_height = Length(
      getNonNegativeDoubleAttribute(xml, "RectRound", "height"), units);
  m_radius = Length(
      getNonNegativeDoubleAttribute(xml, "RectRound", "radius"), units);
  if (2 * m_radius.mil() > m_width.mil() ||
      2 * m_radius.mil() > m_height.mil()) {
    throw new InvalidAttributeError("RectRound", "radius");
  }
  m_upperRight = getBoolAttribute(xml, "upperRight");
  m_upperLeft = getBoolAttribute(xml, "upperLeft");
  m_lowerLeft = getBoolAttribute(xml, "lowerLeft");
  m_lowerRight = getBoolAttribute(xml, "lowerRight");
}

void
RectRound::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  qreal w = m_width.inch(),
        h = m_height.inch(),
        r = m_radius.inch();

  Contour surface;
  surface.polygon().setPolyBegin(QPointF(0, 0.5 * h));
  if (m_upperLeft) {
    surface.polygon().addSegment(QPointF(-0.5 * w + r, 0.5 * h));
    surface.polygon().addCurve(QPointF(-0.5 * w, 0.5 * h - r),
                               QPointF(-0.5 * w + r, 0.5 * h - r),
                               false);
  }
  else {
    surface.polygon().addSegment(QPointF(-0.5 * w, 0.5 * h));
  }
  if (m_lowerLeft) {
    surface.polygon().addSegment(QPointF(-0.5 * w, -0.5 * h + r));
    surface.polygon().addCurve(QPointF(-0.5 * w + r, -0.5 * h),
                               QPointF(-0.5 * w + r, -0.5 * h + r),
                               false);
  }
  else {
    surface.polygon().addSegment(QPointF(-0.5 * w, -0.5 * h));
  }
  if (m_lowerRight) {
    surface.polygon().addSegment(QPointF(0.5 * w - r, -0.5 * h));
    surface.polygon().addCurve(QPointF(0.5 * w, -0.5 * h + r),
                               QPointF(0.5 * w - r, -0.5 * h + r),
                               false);
  }
  else {
    surface.polygon().addSegment(QPointF(0.5 * w, -0.5 * h));
  }
  if (m_upperRight) {
    surface.polygon().addSegment(QPointF(0.5 * w, 0.5 * h - r));
    surface.polygon().addCurve(QPointF(0.5 * w - r, 0.5 * h),
                               QPointF(0.5 * w - r, 0.5 * h - r),
                               false);
  }
  else {
    surface.polygon().addSegment(QPointF(0.5 * w, 0.5 * h));
  }
  surface.polygon().addSegment(QPointF(0, 0.5 * h));

  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
