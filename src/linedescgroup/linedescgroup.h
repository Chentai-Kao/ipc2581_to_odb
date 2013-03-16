#ifndef __LINEDESCGROUP_H__
#define __LINEDESCGROUP_H__

#include <QtCore>

// Base class of "LineDescGroup" substitution group:
// LineDesc
class LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
};

#endif
