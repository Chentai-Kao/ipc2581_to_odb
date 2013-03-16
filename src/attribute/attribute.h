#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include <QtCore>

// Base class of "Attribute" substitution group:
// LineDesc
class Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
};

#endif
