#ifndef __LINEDESCREF_H__
#define __LINEDESCREF_H__

#include "linedescgroup.h"
#include "utils.h"
#include "error.h"
#include "length.h"

class LineDescRef : public LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual Length lineWidth() {
    throw new ProgramLogicError("LineDescRef::lineWidth()");
  }
  
  // getter
  virtual QString endType() { return ""; }
  virtual QString refId() { return m_id; }

private:
  QString m_id;
};

#endif
