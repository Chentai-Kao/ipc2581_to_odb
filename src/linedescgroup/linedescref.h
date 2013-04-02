#ifndef __LINEDESCREF_H__
#define __LINEDESCREF_H__

#include "linedescgroup.h"
#include "utils.h"
#include "error.h"

class LineDescRef : public LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual qreal lineWidth() {
    throw new ProgramLogicError("LineDescRef::lineWidth()");
  }
  virtual QString endType() { return ""; }

private:
  QString m_id;
};

#endif
