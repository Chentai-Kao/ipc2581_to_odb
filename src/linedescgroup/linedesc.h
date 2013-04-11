#ifndef __LINEDESC_H__
#define __LINEDESC_H__

#include "linedescgroup.h"
#include "utils.h"
#include "length.h"

class LineDesc : public LineDescGroup
{
public:
  enum LineEnd { ROUND, SQUARE, NONE };
  LineDesc() {}
  LineDesc(enum LineEnd e, Length w) : m_lineEnd(e), m_lineWidth(w) {}
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);

  // getter
  virtual Length lineWidth() { return m_lineWidth; }
  virtual QString endType() { return (m_lineEnd == SQUARE)? "s" : "r"; }
  virtual QString refId() { return ""; }

private:
  LineEnd m_lineEnd;
  Length m_lineWidth;
};

#endif
