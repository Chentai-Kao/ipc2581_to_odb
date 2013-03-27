#include "linedescgroupfactory.h"
#include "error.h"
#include "linedesc.h"
#include "linedescref.h"

LineDescGroup*
LineDescGroupFactory::create(QStringRef elementName)
{
  if (elementName == "LineDesc") {
    return new LineDesc();
  }
  else if (elementName == "LineDescRef") {
    return new LineDescRef();
  }
  throw new InvalidElementError(elementName);
}
