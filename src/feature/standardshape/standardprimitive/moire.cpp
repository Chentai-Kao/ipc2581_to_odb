#include "moire.h"
#include "error.h"
#include "contour.h"

void
Moire::initialize(QXmlStreamReader& xml, UnitsType units)
{
  // required attributes
  m_diameter = Length(
      getNonNegativeDoubleAttribute(xml, "Moire", "diameter"), units);
  m_ringWidth = Length(
      getNonNegativeDoubleAttribute(xml, "Moire", "ringWidth"), units);
  m_ringGap = Length(
      getNonNegativeDoubleAttribute(xml, "Moire", "ringGap"), units);
  m_ringNumber = getNonNegativeIntAttribute(xml, "Moire", "ringNumber");
  // optional attributes
  m_lineWidth = Length(0, units);
  m_lineLength = Length(0, units);
  m_lineAngle = 0;
  if (hasAttribute(xml, "lineWidth")) {
    m_lineWidth = Length(
        getNonNegativeDoubleAttribute(xml, "Moire", "lineWidth"), units);
  }
  if (hasAttribute(xml, "lineLength")) {
    m_lineLength = Length(
      getNonNegativeDoubleAttribute(xml, "Moire", "lineLength"), units);
  }
  if (hasAttribute(xml, "lineAngle")) {
    m_lineAngle = getNonNegativeDoubleAttribute(xml, "Moire", "lineAngle");
    if (m_lineAngle < 0 || m_lineAngle > 90) {
      throw new InvalidAttributeError("Moire", "lineAngle");
    }
  }
}

void
Moire::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  Contour surface;
  // draw the rings one by one (from outer to inner)
  for (int i = 0; i < m_ringNumber; ++i) {
    surface.clear();
    qreal r = 0.5 * m_diameter.inch() - i * m_ringGap.inch() +
        0.5 * m_ringWidth.inch();
    surface.polygon().setPolyBegin(QPointF(0, r));
    surface.polygon().addCurve(QPointF(0, r), QPointF(0, 0), false);

    r -= m_ringWidth.inch();
    surface.addCutout();
    surface.cutout().setPolyBegin(QPointF(0, r));
    surface.cutout().addCurve(QPointF(0, r), QPointF(0, 0), false);

    surface.odbOutputLayerFeature(file, polarity, location, xform);
  }
  // draw the cross lines
  qreal w = m_lineWidth.inch(),
        h = m_lineLength.inch();
  QPointF p1 = rotatePoint(QPointF( 0.5 * w,  0.5 * h), m_lineAngle),
          p2 = rotatePoint(QPointF(-0.5 * w,  0.5 * h), m_lineAngle),
          p3 = rotatePoint(QPointF(-0.5 * w, -0.5 * h), m_lineAngle),
          p4 = rotatePoint(QPointF( 0.5 * w, -0.5 * h), m_lineAngle);
  for (int i = 0; i < 2; ++i) { // for two lines
    qreal angle = 90 * i;
    p1 = rotatePoint(p1, angle);
    p2 = rotatePoint(p2, angle);
    p3 = rotatePoint(p3, angle);
    p4 = rotatePoint(p4, angle);

    surface.clear();
    surface.polygon().setPolyBegin(p1);
    surface.polygon().addSegment(p2);
    surface.polygon().addSegment(p3);
    surface.polygon().addSegment(p4);
    surface.polygon().addSegment(p1);
    surface.odbOutputLayerFeature(file, polarity, location, xform);
  }
}
