#include "userprimitivefactory.h"
#include "simplefactory.h"
#include "text.h"
#include "userspecial.h"
#include "error.h"

UserPrimitive*
UserPrimitiveFactory::create(QStringRef elementName)
{
  if (elementName == "Text") {
    return new Text();
  }
  else if (elementName == "UserSpecial") {
    return new UserSpecial();
  }
  else if (elementName == "Arc" ||
           elementName == "Line" ||
           elementName == "Outline" ||
           elementName == "Polyline") {
    return SimpleFactory().create(elementName);
  }
  throw new InvalidElementError(elementName);
}
