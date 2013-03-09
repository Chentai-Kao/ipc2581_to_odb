#ifndef __ARC_H__
#define __ARC_H__

#include "userprimitive.h"
#include "linedesc.h"
#include "linedescgroup.h"
#include "linedescref.h"

class Arc : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  QPointF m_start; // (startX, startY)
  QPointF m_end; // (endX, endY)
  QPointF m_center; // (centerX, centerY)
  bool m_clockwise;
  LineDescGroup* m_lineDescGroup;
};

#endif
