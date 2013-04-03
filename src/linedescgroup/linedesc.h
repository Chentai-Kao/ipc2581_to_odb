#ifndef __LINEDESC_H__
#define __LINEDESC_H__

#include "linedescgroup.h"
#include "utils.h"

class LineDesc : public LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  enum LineEnd { ROUND, SQUARE, NONE };

  // getter
  virtual qreal lineWidth() { return m_lineWidth; }
  virtual QString endType() { return (m_lineEnd == SQUARE)? "s" : "r"; }
  virtual QString refId() { return ""; }

private:
  LineEnd m_lineEnd;
  qreal m_lineWidth;
};

#endif
