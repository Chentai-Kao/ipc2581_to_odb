#include "rectcham.h"
#include "error.h"
#include "contour.h"

void
RectCham::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_width = Length(
      getNonNegativeDoubleAttribute(xml, "RectCham", "width"), units);
  m_height = Length(
      getNonNegativeDoubleAttribute(xml, "RectCham", "height"), units);
  m_chamfer = Length(
      getNonNegativeDoubleAttribute(xml, "RectCham", "chamfer"), units);
  if (2 * m_chamfer.mil() > m_width.mil() ||
      2 * m_chamfer.mil() > m_height.mil()) {
    throw new InvalidAttributeError("RectCham", "chamfer");
  }
  m_upperRight = getBoolAttribute(xml, "upperRight");
  m_upperLeft = getBoolAttribute(xml, "upperLeft");
  m_lowerLeft = getBoolAttribute(xml, "lowerLeft");
  m_lowerRight = getBoolAttribute(xml, "lowerRight");
}

void
RectCham::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  qreal w = m_width.inch(),
        h = m_height.inch(),
        c = m_chamfer.inch();

  Contour surface;
  surface.polygon().setPolyBegin(QPointF(0, 0.5 * h));
  if (m_upperLeft) {
    surface.polygon().addSegment(QPointF(-0.5 * w + c, 0.5 * h));
    surface.polygon().addSegment(QPointF(-0.5 * w, 0.5 * h - c));
  }
  else {
    surface.polygon().addSegment(QPointF(-0.5 * w, 0.5 * h));
  }
  if (m_lowerLeft) {
    surface.polygon().addSegment(QPointF(-0.5 * w, -0.5 * h + c));
    surface.polygon().addSegment(QPointF(-0.5 * w + c, -0.5 * h));
  }
  else {
    surface.polygon().addSegment(QPointF(-0.5 * w, -0.5 * h));
  }
  if (m_lowerRight) {
    surface.polygon().addSegment(QPointF(0.5 * w - c, -0.5 * h));
    surface.polygon().addSegment(QPointF(0.5 * w, -0.5 * h + c));
  }
  else {
    surface.polygon().addSegment(QPointF(0.5 * w, -0.5 * h));
  }
  if (m_upperRight) {
    surface.polygon().addSegment(QPointF(0.5 * w, 0.5 * h - c));
    surface.polygon().addSegment(QPointF(0.5 * w - c, 0.5 * h));
  }
  else {
    surface.polygon().addSegment(QPointF(0.5 * w, 0.5 * h));
  }
  surface.polygon().addSegment(QPointF(0, 0.5 * h));

  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
