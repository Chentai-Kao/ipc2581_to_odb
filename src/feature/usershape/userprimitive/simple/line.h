#ifndef __LINE_H__
#define __LINE_H__

#include "simple.h"
#include "linedesc.h"
#include "linedescgroup.h"
#include "linedescref.h"

class Line : public Simple
{
public:
  Line() {}
  Line(QPointF s, QPointF e, LineDescGroup *l) :
      m_start(s), m_end(e), m_lineDescGroup(l) {}
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  QPointF m_start; // (startX, startY)
  QPointF m_end; // (endX, endY)
  LineDescGroup *m_lineDescGroup;
};

#endif
