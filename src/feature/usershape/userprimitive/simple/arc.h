#ifndef __ARC_H__
#define __ARC_H__

#include "simple.h"
#include "linedesc.h"
#include "linedescgroup.h"
#include "linedescref.h"

class Arc : public Simple
{
public:
  Arc() {}
  Arc(QPointF s, QPointF e, QPointF c, bool cw, LineDescGroup *l) :
      m_start(s), m_end(e), m_center(c), m_clockwise(cw), m_lineDescGroup(l) {}
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  QPointF m_start; // (startX, startY)
  QPointF m_end; // (endX, endY)
  QPointF m_center; // (centerX, centerY)
  bool m_clockwise;
  LineDescGroup *m_lineDescGroup;
};

#endif
