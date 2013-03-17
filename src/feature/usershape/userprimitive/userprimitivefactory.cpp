#include "userprimitivefactory.h"
#include "simplefactory.h"
#include "text.h"
#include "userspecial.h"

UserPrimitive*
UserPrimitiveFactory::create(QStringRef elementName)
{
  UserPrimitive *u = SimpleFactory().create(elementName);
  if (u != NULL) {
    return u;
  }

  if (elementName == "Text") {
    return new Text();
  }
  else if (elementName == "UserSpecial") {
    return new UserSpecial();
  }
  return NULL;
}
