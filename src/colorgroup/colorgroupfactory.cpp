#include "colorgroupfactory.h"
#include "color.h"
#include "colorref.h"

ColorGroup*
ColorGroupFactory::create(QStringRef elementName)
{
  if (elementName == "Color") {
    return new Color();
  }
  else if (elementName == "ColorRef") {
    return new ColorRef();
  }
  return NULL;
}
