#ifndef __POLYLINE_H__
#define __POLYLINE_H__

#include "userprimitive.h"
#include "polystep.h"
#include "polystepcurve.h"
#include "polystepsegment.h"
#include "linedesc.h"
#include "linedescgroup.h"
#include "linedescref.h"

class Polyline : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  QPointF m_polyBegin;
  QList<PolyStep*> m_polySteps;
  LineDescGroup* m_lineDescGroup;
};

#endif
