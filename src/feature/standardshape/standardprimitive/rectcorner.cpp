#include "rectcorner.h"
#include "contour.h"

void
RectCorner::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_lowerLeftX = Length(
      getDoubleAttribute(xml, "RectCorner", "lowerLeftX"), units);
  m_lowerLeftY = Length(
      getDoubleAttribute(xml, "RectCorner", "lowerLeftY"), units);
  m_upperRightX = Length(
      getDoubleAttribute(xml, "RectCorner", "upperRightX"), units);
  m_upperRightY = Length(
      getDoubleAttribute(xml, "RectCorner", "upperRightY"), units);
}

void
RectCorner::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  qreal llx = m_lowerLeftX.inch();
  qreal lly = m_lowerLeftY.inch();
  qreal urx = m_upperRightX.inch();
  qreal ury = m_upperRightY.inch();

  Contour surface;
  surface.polygon().setPolyBegin(QPointF(urx, ury));
  surface.polygon().addSegment(QPointF(llx, ury));
  surface.polygon().addSegment(QPointF(llx, lly));
  surface.polygon().addSegment(QPointF(urx, lly));
  surface.polygon().addSegment(QPointF(urx, ury));
  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
