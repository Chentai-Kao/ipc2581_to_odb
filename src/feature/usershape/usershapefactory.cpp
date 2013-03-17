#include "usershapefactory.h"
#include "userprimitivefactory.h"
#include "userprimitiveref.h"

UserShape*
UserShapeFactory::create(QStringRef elementName)
{
  UserShape *u = UserPrimitiveFactory().create(elementName);
  if (u != NULL) {
    return u;
  }
  if (elementName == "UserPrimitiveRef") {
    return new UserPrimitiveRef();
  }
  return NULL;
}
