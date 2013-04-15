#include "donut.h"
#include "error.h"
#include "line.h"
#include "linedesc.h"
#include "polygon.h"
#include "contour.h"

void
Donut::initialize(QXmlStreamReader& xml, UnitsType units)
{
  // shape
  QString shape = getStringAttribute(xml, "Donut", "shape");
  if (shape == "ROUND") {
    m_shape = ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = SQUARE;
  }
  else if (shape == "HEXAGON") {
    m_shape = HEXAGON;
  }
  else if (shape == "OCTAGON") {
    m_shape = OCTAGON;
  }
  // outerDiameter/innerDiameter
  m_outerDiameter = Length(
      getNonNegativeDoubleAttribute(xml, "Donut", "outerDiameter"), units);
  m_innerDiameter = Length(
      getNonNegativeDoubleAttribute(xml, "Donut", "innerDiameter"), units);
}

void
Donut::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  qreal od = m_outerDiameter.inch();
  qreal id = m_innerDiameter.inch();
  Contour surface;
  if (m_shape == ROUND) {
    surface.polygon().setPolyBegin(QPointF(0, 0.5 * od));
    surface.polygon().addCurve(QPointF(0, 0.5 * od), QPointF(0, 0), false);

    surface.addCutout();
    surface.cutout().setPolyBegin(QPointF(0, 0.5 * id));
    surface.cutout().addCurve(QPointF(0, 0.5 * id), QPointF(0, 0), false);
  }
  else if (m_shape == SQUARE) {
    surface.polygon().setPolyBegin(QPointF(0.5 * od,  0.5 * od));
    surface.polygon().addSegment(QPointF( -0.5 * od,  0.5 * od));
    surface.polygon().addSegment(QPointF( -0.5 * od, -0.5 * od));
    surface.polygon().addSegment(QPointF(  0.5 * od, -0.5 * od));
    surface.polygon().addSegment(QPointF(  0.5 * od,  0.5 * od));

    surface.addCutout();
    surface.cutout().setPolyBegin(QPointF(0.5 * id,  0.5 * id));
    surface.cutout().addSegment(QPointF( -0.5 * id,  0.5 * id));
    surface.cutout().addSegment(QPointF( -0.5 * id, -0.5 * id));
    surface.cutout().addSegment(QPointF(  0.5 * id, -0.5 * id));
    surface.cutout().addSegment(QPointF(  0.5 * id,  0.5 * id));
  }
  else if (m_shape == HEXAGON) {
    QPointF p(0, 0.5 * od);
    surface.polygon().setPolyBegin(p);
    for (int i = 0; i < 6; ++i) {
      p = rotatePoint(p, 60);
      surface.polygon().addSegment(p);
    }

    surface.addCutout();
    p = QPointF(0, 0.5 * id);
    surface.cutout().setPolyBegin(p);
    for (int i = 0; i < 6; ++i) {
      p = rotatePoint(p, 60);
      surface.cutout().addSegment(p);
    }
  }
  else if (m_shape == OCTAGON) {
    QPointF p(0, 0.5 * od);
    surface.polygon().setPolyBegin(p);
    for (int i = 0; i < 8; ++i) {
      p = rotatePoint(p, 45);
      surface.polygon().addSegment(p);
    }

    surface.addCutout();
    p = QPointF(0, 0.5 * id);
    surface.cutout().setPolyBegin(p);
    for (int i = 0; i < 8; ++i) {
      p = rotatePoint(p, 45);
      surface.cutout().addSegment(p);
    }
  }
  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
