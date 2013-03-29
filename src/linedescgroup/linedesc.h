#ifndef __LINEDESC_H__
#define __LINEDESC_H__

#include "linedescgroup.h"

class LineDesc : public LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  enum LineEnd { ROUND, SQUARE, NONE };

  // getter
  virtual qreal lineWidth() { return m_lineWidth; }

private:
  LineEnd m_lineEnd;
  qreal m_lineWidth;
};

#endif
