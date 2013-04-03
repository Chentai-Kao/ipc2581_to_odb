#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <QtCore>
#include "polystep.h"
#include "xform.h"
#include "utils.h"
#include "odbfeaturefile.h"

class Polygon
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform, PolygonType type);

private:
  // member function
  bool isClosedShape();
  bool isClockwise();
  QList<PolygonEdge> calcPolygonEdges();
  // output feature in inverse order or not
  void odbOutputFeature(OdbFeatureFile& file, PolygonType type);
  void odbOutputFeatureInv(OdbFeatureFile& file, PolygonType type);

  // data member
  QPointF m_polyBegin;
  QList<PolyStep*> m_polySteps;
};

#endif
