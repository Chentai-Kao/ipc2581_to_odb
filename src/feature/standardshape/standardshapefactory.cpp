#include "standardshapefactory.h"
#include "standardprimitivefactory.h"
#include "standardprimitiveref.h"

StandardShape*
StandardShapeFactory::create(QStringRef elementName)
{
  StandardShape *s = StandardPrimitiveFactory().create(elementName);
  if (s != NULL) {
    return s;
  }
  if (elementName == "StandardPrimitiveRef") {
    return new StandardPrimitiveRef();
  }
  return NULL;
}
