#include <cassert>
#include "thermal.h"
#include "error.h"
#include "donut.h"
#include "polygon.h"

void
Thermal::initialize(QXmlStreamReader& xml, UnitsType units)
{
  // shape
  QString shape = getStringAttribute(xml, "Thermal", "shape");
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
  // others...
  m_outerDiameter = toMil(
      getDoubleAttribute(xml, "Thermal", "outerDiameter"), units);
  m_innerDiameter = toMil(
      getDoubleAttribute(xml, "Thermal", "innerDiameter"), units);
  if (hasAttribute(xml, "spokeCount")) {
    m_spokeCount = getIntAttribute(xml, "Thermal", "spokeCount");
    if (!isValidSpokeCount()) {
      throw new InvalidAttributeError("Thermal", "spokeCount");
    }
  }
  else {
    m_spokeCount = (m_shape == HEXAGON)? 3 : 4;
  }
  if (hasAttribute(xml, "gap")) {
    m_gap = toMil(
        getNonNegativeDoubleAttribute(xml, "Thermal", "gap"), units);
  }
  else {
    m_gap = m_outerDiameter - m_innerDiameter;
  }
  // make sure start angle is between 0 ~ 360 degree
  m_spokeStartAngle = getDoubleAttribute(xml, "Thermal", "spokeStartAngle");
  m_spokeStartAngle = equalAngle(m_spokeStartAngle);
}

bool
Thermal::isValidSpokeCount()
{
  switch (m_shape) {
    case ROUND :
      return (m_spokeCount == 0 || m_spokeCount == 2 ||
              m_spokeCount == 3 || m_spokeCount == 4);
    case SQUARE :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 4);
    case HEXAGON :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 3);
    case OCTAGON :
      return (m_spokeCount == 0 || m_spokeCount == 2 || m_spokeCount == 4);
    default :
      break;
  }
  return true;
}

void
Thermal::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol;
  if (m_shape == ROUND) {
    symbol = QString("ths%1x%2x%3x%4x%5")
                     .arg(m_outerDiameter)
                     .arg(m_innerDiameter)
                     .arg(m_spokeStartAngle)
                     .arg(m_spokeCount)
                     .arg(m_gap);
  }
  else if (m_shape == SQUARE) {
    symbol = QString("s_ths%1x%2x%3x%4x%5")
                     .arg(m_outerDiameter)
                     .arg(m_innerDiameter)
                     .arg(m_spokeStartAngle)
                     .arg(m_spokeCount)
                     .arg(m_gap);
  }
  else if (m_shape == HEXAGON || m_shape == OCTAGON) {
    if (m_spokeCount == 0 || m_gap == 0) { // no spoke at all, same as donut
      Donut donut(m_shape, m_outerDiameter, m_innerDiameter);
      donut.odbOutputLayerFeature(file, polarity, location, xform);
    }
    else {
      file.featuresList().append(QString("S %1 0\n").arg(polarity));
      drawSegmentWithSpoke(file, location, xform);
      file.featuresList().append(QString("SE\n"));
    }
    return;
  }

  int symNum = odbInsertSymbol(symbol, file.symbolsTable());
  QPointF newLocation = calcTransformedLocation(location, xform);
  int orient = odbDecideOrient(xform);
  file.featuresList().append(QString("P %1 %2 %3 %4 0 %5\n")
                             .arg(newLocation.x())
                             .arg(newLocation.y())
                             .arg(symNum)
                             .arg(polarity)
                             .arg(orient));
}

void
Thermal::drawSegmentWithSpoke(
    OdbFeatureFile& file, QPointF location, Xform *xform)
{
  assert(m_spokeCount != 0);

  // find 4 kinds of intersections: "outer/inner <--> left/right end"
  QList<Intersection> outerLeftEnds, outerRightEnds,
                      innerLeftEnds, innerRightEnds;
  calcSpokeIntersection(
      outerLeftEnds, outerRightEnds, innerLeftEnds, innerRightEnds);

  // Method:
  // for each intersection in "outer RIGHT_END":
  //   walk through vertex counter-clockwisely, find the next "outer LEFT_END"
  //   find its corresponding "inner LEFT_END"
  //   walk through vertex clockwisely, find the next "inner RIGHT_END"
  //   close the shape, call Polygon to draw
  QList<QPointF> points; // hold the vertex of the final Polygon
  QList<QPointF> vertex; // hold the vertex while walking through
  qreal startAngle, endAngle; // the angle range to walk through
  for (int i = 0; i < outerRightEnds.size(); ++i) {
    int startIdx = i;
    int endIdx = (i + 1) % outerRightEnds.size();
    points.clear();
    points.append(outerRightEnds[startIdx].m_point); // beginning point
    walkThrough(vertex, false, m_outerDiameter, // walk counter-clockwisely
        outerRightEnds[startIdx].m_angle,
        outerLeftEnds[endIdx].m_angle);
    points.append(vertex); // append the walked through vertex
    points.append(outerLeftEnds[endIdx].m_point); // corr' "outer LEFT_END"
    points.append(innerLeftEnds[endIdx].m_point); // corr' "inner LEFT_END"
    walkThrough(vertex, true , m_innerDiameter, // walk clockwisely
        innerLeftEnds[endIdx].m_angle,
        innerRightEnds[startIdx].m_angle);
    points.append(vertex); // append the walked through vertex
    points.append(innerRightEnds[startIdx].m_point); // corr' "inner RIGHT_END"
    points.append(outerRightEnds[startIdx].m_point); // close shape

    // convert the unit to inch
    milToInch(points);

    // output as polygon
    Polygon polygon;
    polygon.setPolygon(points);
    polygon.odbOutputLayerFeature(file, location, xform, POLYGON);
  }
}

void
Thermal::calcSpokeIntersection(
    QList<Intersection>& outerLeftEnds,
    QList<Intersection>& outerRightEnds,
    QList<Intersection>& innerLeftEnds,
    QList<Intersection>& innerRightEnds)
{
  calcIntersectionSet(outerLeftEnds, m_outerDiameter, LEFT_END);
  calcIntersectionSet(outerRightEnds, m_outerDiameter, RIGHT_END);
  calcIntersectionSet(innerLeftEnds, m_innerDiameter, LEFT_END);
  calcIntersectionSet(innerRightEnds, m_innerDiameter, RIGHT_END);
}

Thermal::Intersection
Thermal::calcIntersection(
    qreal angle, qreal diameter, SpokeSegmentEndType endType)
{
  /* Method: (the target is p0(x0,y0))
   * 1. create all vertex of a normal hexagon
   * 2. rotate all vertex to desired 'angle'
   * 3. set value of x0. LEFT_END: "x0 = 0.5 gap"; RIGHT_END: "x0 = -0.5 gap"
   * 4. find vertex p1, p2 that enclose the line "x = x0".
   *    the relation is like:  p1-----p0------------p2 (p1 at left, p2 at right)
   * 5. use interpolation to find y0 (given p1 and p2)
   *    ratio:     (m)       (n)          (m + n = 1)
   *            p1-----p0------------p2
   * 6. rotate p0 back to spoke start angle, then return p0
   */
  int nVertex = (m_shape == HEXAGON)? 6 : 8; // number of vertex
  // step 1, step 2
  QList<QPointF> vertex; // all vertex. ordered counter-clockwisely.
  for (int i = 0; i < nVertex; ++i) {
    QPointF v(0, 0.5 * diameter);
    v = rotatePoint(v, i * (360 / nVertex)); // step 1
    v = rotatePoint(v, 90 - angle); // step 2
    vertex.append(v);
  }
  // step 3
  qreal x0 = (endType == LEFT_END)? (0.5 * m_gap) : (-0.5 * m_gap);
  // step 4
  QPointF p1, p2;
  for (int i = 0; i < nVertex; ++i) {
    p1 = vertex[(i + 1) % nVertex]; // this ensures the relation:
    p2 = vertex[i];                 // p1-----p0------------p2
    if (p1.x() < x0 && x0 <= p2.x()) { // find p1, p2 that enclose "x = x0"
      break;
    }
  }
  // step 5
  qreal m = (x0 - p1.x()) / (p2.x() - p1.x());
  qreal n = (p2.x() - x0) / (p2.x() - p1.x());
  qreal y0 = p1.y() * n + p2.y() * m;
  // step 6
  QPointF p0(x0, y0);
  p0 = rotatePoint(p0, -(90 - angle));
  Intersection inter;
  inter.m_point = p0;
  inter.m_angle = angle;
  return inter;
}

void
Thermal::calcIntersectionSet(
    QList<Intersection>& intersectionSet,
    qreal diameter,
    SpokeSegmentEndType endType)
{
  intersectionSet.clear();

  // the amount of angle to rotate the first intersection to get each of others
  qreal diffAngle = 360 / m_spokeCount;

  // collect all intersections
  for (int i = 0; i < m_spokeCount; ++i) {
    qreal angle = equalAngle(m_spokeStartAngle + i * diffAngle);
    Intersection s = calcIntersection(angle, diameter, endType);
    intersectionSet.append(s);
  }
}

void
Thermal::walkThrough(QList<QPointF>& vertex, bool isClockwise, qreal diameter,
    qreal startAngle, qreal endAngle)
{
  assert(0 <= startAngle && startAngle < 360 &&
         0 <= endAngle   && endAngle   < 360);
  vertex.clear();
  qreal stepAngle = (m_shape == HEXAGON)? 60 : 45;
  if (!isClockwise) { // counter-clockwise
    if (endAngle < startAngle) { // make sure end angle is bigger
      endAngle += 360;
    }
    qreal angle = ceilToVertex(startAngle);
    while (angle < endAngle) {
      vertex.append(rotatePoint(QPointF(0.5 * diameter, 0), angle));
      angle += stepAngle;
    }
  }
  else { // clockwise
    if (endAngle > startAngle) {
      startAngle += 360;
    }
    qreal angle = floorToVertex(startAngle);
    while (angle > endAngle) {
      vertex.append(rotatePoint(QPointF(0.5 * diameter, 0), angle));
      angle -= stepAngle;
    }
  }
}

qreal
Thermal::ceilToVertex(qreal angle)
{
  qreal n;
  if (m_shape == HEXAGON) { // hexagon
    n = 30;
    while (n <= angle) {
      n += 60;
    }
  }
  else { // octagon
    n = 0;
    while (n <= angle) {
      n += 45;
    }
  }
  return n;
}

qreal
Thermal::floorToVertex(qreal angle)
{
  qreal n;
  if (m_shape == HEXAGON) { // hexagon
    n = 810;
    while (n >= angle) {
      n -= 60;
    }
  }
  else { // octagon
    n = 720;
    while (n >= angle) {
      n -= 45;
    }
  }
  return n;
}
