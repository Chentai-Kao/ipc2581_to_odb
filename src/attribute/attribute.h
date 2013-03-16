#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include <QtCore>

// Base class of "Attribute" substitution group:
// BooleanAttribute, DoubleAttribute, IntegerAttribute, NonstandardAttribute,
// OptionAttribute, TextAttribute
class Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
};

#endif
