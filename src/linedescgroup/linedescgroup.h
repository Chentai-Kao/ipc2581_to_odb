#ifndef __LINEDESCGROUP_H__
#define __LINEDESCGROUP_H__

#include <QtCore>
#include "utils.h"
#include "length.h"

// Base class of "LineDescGroup" substitution group:
// LineDesc
class LineDescGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units) = 0;
  virtual Length lineWidth() = 0;
  virtual QString endType() = 0;
  virtual QString refId() = 0;
};

#endif
