#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <QtCore>
#include "polystep.h"
#include "xform.h"
#include "utils.h"

class Polygon
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  virtual void odbOutputLayerFeature(
      QList<QString>& symbolsTable,
      QList<QString>& attributeTable,
      QList<QString>& attributeTexts,
      QList<QString>& featuresList,
      QString polarity,
      QPointF location, Xform *xform, PolygonType type);

private:
  // member function
  bool isClosedShape();
  bool isClockwise();
  QList<PolygonEdge> calcPolygonEdges();
  // output feature in inverse order or not
  void odbOutputFeature(QList<QString>& featuresList, PolygonType type);
  void odbOutputFeatureInv(QList<QString>& featuresList, PolygonType type);

  // data member
  QPointF m_polyBegin;
  QList<PolyStep*> m_polySteps;
};

#endif
