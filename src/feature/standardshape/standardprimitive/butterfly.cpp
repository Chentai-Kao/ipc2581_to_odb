#include "butterfly.h"
#include "error.h"
#include "contour.h"

void
Butterfly::initialize(QXmlStreamReader& xml, UnitsType units)
{
  // shape
  QString shape = getStringAttribute(xml, "Butterfly", "shape");
  if (shape == "ROUND") {
    m_shape = ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = SQUARE;
  }
  else {
    throw new InvalidAttributeError("Butterfly", "shape");
  }
  // diameter and side
  if (m_shape == ROUND) {
    m_diameter = Length(
        getNonNegativeDoubleAttribute(xml, "Butterfly", "diameter"), units);
  }
  else if (m_shape == SQUARE) {
    m_side = Length(
        getNonNegativeDoubleAttribute(xml, "Butterfly", "side"), units);
  }
}

void
Butterfly::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  qreal r = (m_shape == ROUND)? m_diameter.inch() : m_side.inch();
  Contour left, right; // left wing and right wing
  if (m_shape == ROUND) {
    left.polygon().setPolyBegin(QPointF(0, 0));
    left.polygon().addSegment(QPointF(0, 0.5 * r));
    left.polygon().addCurve(QPointF(-0.5 * r, 0), QPointF(0, 0), false);
    left.polygon().addSegment(QPointF(0, 0));

    right.polygon().setPolyBegin(QPointF(0, 0));
    right.polygon().addSegment(QPointF(0.5 * r, 0));
    right.polygon().addCurve(QPointF(0, -0.5 * r), QPointF(0, 0), true);
    right.polygon().addSegment(QPointF(0, 0));
  }
  else {
    left.polygon().setPolyBegin(QPointF(0, 0));
    left.polygon().addSegment(QPointF(0, 0.5 * r));
    left.polygon().addSegment(QPointF(-0.5 * r, 0.5 * r));
    left.polygon().addSegment(QPointF(-0.5 * r, 0));
    left.polygon().addSegment(QPointF(0, 0));

    right.polygon().setPolyBegin(QPointF(0, 0));
    right.polygon().addSegment(QPointF(0.5 * r, 0));
    right.polygon().addSegment(QPointF(0.5 * r, -0.5 * r));
    right.polygon().addSegment(QPointF(0, -0.5 * r));
    right.polygon().addSegment(QPointF(0, 0));
  }
  left.odbOutputLayerFeature(file, polarity, location, xform);
  right.odbOutputLayerFeature(file, polarity, location, xform);
}
