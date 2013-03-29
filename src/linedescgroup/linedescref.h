#ifndef __LINEDESCREF_H__
#define __LINEDESCREF_H__

#include "linedescgroup.h"
#include "error.h"

class LineDescRef : public LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  virtual qreal lineWidth() {
    throw new ProgramLogicError("LineDescRef::lineWidth()");
  }

private:
  QString m_id;
};

#endif
