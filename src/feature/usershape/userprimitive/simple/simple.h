#ifndef __SIMPLE_H__
#define __SIMPLE_H__

#include <QtCore>
#include "utils.h"
#include "userprimitive.h"

// Base class of "Simple":
// Arc, Line, Outline, Polyline
class Simple : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
};

#endif
