#include "featurefactory.h"
#include "standardshapefactory.h"
#include "usershapefactory.h"

Feature*
FeatureFactory::create(QStringRef elementName)
{
  Feature *f = StandardShapeFactory().create(elementName);
  if (f != NULL) {
    return f;
  }
  f = UserShapeFactory().create(elementName);
  if (f != NULL) {
    return f;
  }
  return NULL;
}
