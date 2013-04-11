#ifndef __THERMAL_H__
#define __THERMAL_H__

#include "standardprimitive.h"
#include "utils.h"
#include "length.h"

class Thermal : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  bool isValidSpokeCount();
  enum SpokeSegmentEndType { LEFT_END, RIGHT_END };
  struct Intersection {
    QPointF m_point; // the intersection point
    qreal   m_angle; // angle of the intersection (0~360)
  };
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  // member function
  void drawSegmentWithSpoke(
      OdbFeatureFile& file, QPointF location, Xform *xform);
  void calcSpokeIntersection(
      QList<Intersection>& outerLeftEnds,
      QList<Intersection>& outerRightEnds,
      QList<Intersection>& innerLeftEnds,
      QList<Intersection>& innerRightEnds);
  Intersection calcIntersection(
      qreal angle, qreal diameter, SpokeSegmentEndType endType);
  void calcIntersectionSet(
      QList<Intersection>& intersectionSet,
      qreal diameter,
      SpokeSegmentEndType endType);
  void walkThrough(QList<QPointF>& vertex, bool isClockwise, qreal diameter,
      qreal startAngle, qreal endAngle);
  qreal ceilToVertex(qreal angle);
  qreal floorToVertex(qreal angle);

  // data member
  Shape m_shape;
  Length m_outerDiameter;
  Length m_innerDiameter;
  int   m_spokeCount;
  Length m_gap;
  qreal m_spokeStartAngle;
};

#endif
