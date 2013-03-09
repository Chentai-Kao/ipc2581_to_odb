#ifndef __LINEDESC_H__
#define __LINEDESC_H__

#include "linedescgroup.h"

class LineDesc : public LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  enum LineEnd { ROUND, SQUARE, NONE } m_lineEnd;
  qreal m_lineWidth;
};

#endif
