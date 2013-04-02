#ifndef __POLYLINE_H__
#define __POLYLINE_H__

#include "simple.h"
#include "polystep.h"
#include "polystepcurve.h"
#include "polystepsegment.h"
#include "linedesc.h"
#include "linedescgroup.h"
#include "linedescref.h"

class Polyline : public Simple
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  QPointF m_polyBegin;
  QList<PolyStep*> m_polySteps;
  LineDescGroup* m_lineDescGroup;
};

#endif
