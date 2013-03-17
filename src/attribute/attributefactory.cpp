#include "attributefactory.h"
#include "booleanattribute.h"
#include "doubleattribute.h"
#include "integerattribute.h"
#include "nonstandardattribute.h"
#include "optionattribute.h"
#include "textattribute.h"

Attribute*
AttributeFactory::create(QStringRef elementName)
{
  if (elementName == "BooleanAttribute") {
    return new BooleanAttribute();
  }
  else if (elementName == "DoubleAttribute") {
    return new DoubleAttribute();
  }
  else if (elementName == "IntegerAttribute") {
    return new IntegerAttribute();
  }
  else if (elementName == "NonstandardAttribute") {
    return new NonstandardAttribute();
  }
  else if (elementName == "OptionAttribute") {
    return new OptionAttribute();
  }
  else if (elementName == "TextAttribute") {
    return new TextAttribute();
  }
  return NULL;
}
