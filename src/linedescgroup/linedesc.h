#ifndef __LINEDESC_H__
#define __LINEDESC_H__

#include "linedescgroup.h"

class LineDesc : public LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  enum LineEnd { ROUND, SQUARE, NONE };

private:
  LineEnd m_lineEnd;
  qreal m_lineWidth;
};

#endif
