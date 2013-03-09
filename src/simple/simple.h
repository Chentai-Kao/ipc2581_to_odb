#ifndef __SIMPLE_H__
#define __SIMPLE_H__

#include <QtCore>
#include "utils.h"

// Base class of "Simple" substitution group:
// Arc, Line, Outline, Polyline
class Simple
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
};

#endif
