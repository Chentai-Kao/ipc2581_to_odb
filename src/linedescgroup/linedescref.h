#ifndef __LINEDESCREF_H__
#define __LINEDESCREF_H__

#include "linedescgroup.h"

class LineDescRef : public LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  QString m_id;
};

#endif
