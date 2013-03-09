#ifndef __COLORGROUP_H__
#define __COLORGROUP_H__

#include <QtCore>
#include "utils.h"

// Base class of "ColorGroup" substitution group:
// Color, ColorRef
class ColorGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
};

#endif
