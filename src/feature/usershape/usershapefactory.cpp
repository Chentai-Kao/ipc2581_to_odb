#include "usershapefactory.h"
#include "userprimitivefactory.h"
#include "userprimitiveref.h"
#include "error.h"

UserShape*
UserShapeFactory::create(QStringRef elementName)
{
  if (elementName == "UserPrimitiveRef") {
    return new UserPrimitiveRef();
  }
  else if (elementName == "Text" ||
           elementName == "UserSpecial" ||
           elementName == "Arc" ||
           elementName == "Line" ||
           elementName == "Outline" ||
           elementName == "Polyline") {
    return UserPrimitiveFactory().create(elementName);
  }
  throw new InvalidElementError(elementName);
}
