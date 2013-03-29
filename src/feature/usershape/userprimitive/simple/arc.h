#ifndef __ARC_H__
#define __ARC_H__

#include "simple.h"
#include "linedesc.h"
#include "linedescgroup.h"
#include "linedescref.h"

class Arc : public Simple
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  QPointF m_start; // (startX, startY)
  QPointF m_end; // (endX, endY)
  QPointF m_center; // (centerX, centerY)
  bool m_clockwise;
  LineDescGroup* m_lineDescGroup;
};

#endif
