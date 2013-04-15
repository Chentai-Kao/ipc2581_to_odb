#include "ellipse.h"
#include "contour.h"

void
Ellipse::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_width = Length(
      getNonNegativeDoubleAttribute(xml, "Ellipse", "width"), units);
  m_height = Length(
      getNonNegativeDoubleAttribute(xml, "Ellipse", "height"), units);
}

void
Ellipse::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  /* Method:
   * use the parametric representation x = a*cos(theta), y = b*sin(theta)
   * as sample points for the polygon.
   * By L. B. Smith's paper "Drawing ellipses, hyperbolas or parabolas...",
   * this method ensures maximum area of enclosed polygon.
   */
  const int n = 1000; // number of points (increase this for higher resolution)
  qreal a = 0.5 * m_width.inch();
  qreal b = 0.5 * m_height.inch();
  qreal dTheta = 2 * M_PI / n;
  Contour surface;
  surface.polygon().setPolyBegin(QPointF(a, 0));
  for (int i = 1; i < n; ++i) {
    qreal theta = i * dTheta;
    qreal x = a * qCos(theta);
    qreal y = b * qSin(theta);
    surface.polygon().addSegment(QPointF(x, y));
  }
  surface.odbOutputLayerFeature(file, polarity, location, xform);
}
