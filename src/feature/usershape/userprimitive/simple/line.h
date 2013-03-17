#ifndef __LINE_H__
#define __LINE_H__

#include "simple.h"
#include "linedesc.h"
#include "linedescgroup.h"
#include "linedescref.h"

class Line : public Simple
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  QPointF m_start; // (startX, startY)
  QPointF m_end; // (endX, endY)
  LineDescGroup* m_lineDescGroup;
};

#endif
