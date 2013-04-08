#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <QtCore>
#include "polystep.h"
#include "xform.h"
#include "utils.h"
#include "odbfeaturefile.h"
#include "simple.h"
#include "arc.h"
#include "line.h"
#include "linedescgroup.h"

class Polygon
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QPointF location, Xform *xform, PolygonType type);

  // setter (for customized polygon, e.g. PolyLine)
  void setPolyBegin(QPointF p) { m_polyBegin = p; }
  void setPolySteps(QList<PolyStep*>& s) { m_polySteps = s; }

  // convert to "Arc + Line" list, so <Outline> can print them all
  void toArcLine(QList<Simple*>& arcLineList, LineDescGroup *lineDescGroup);
  enum OutputOrder { FORWARD, REVERSE };

private:
  // member function
  bool isClosedShape();
  bool isClockwise();
  QList<PolygonEdge> calcPolygonEdges(OutputOrder outputOrder);
  // output feature in inverse order or not
  void odbOutputFeature(OdbFeatureFile& file, QPointF location,
      Xform *xform, PolygonType type, OutputOrder outputOrder);

  // data member
  QPointF m_polyBegin;
  QList<PolyStep*> m_polySteps;
};

#endif
