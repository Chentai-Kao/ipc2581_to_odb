#include "featurefactory.h"
#include "standardshapefactory.h"
#include "usershapefactory.h"
#include "error.h"

Feature*
FeatureFactory::create(QStringRef elementName)
{
  if (elementName == "StandardPrimitiveRef" ||
      elementName == "Butterfly" ||
      elementName == "Circle" ||
      elementName == "Contour" ||
      elementName == "Diamond" ||
      elementName == "Donut" ||
      elementName == "Ellipse" ||
      elementName == "Hexagon" ||
      elementName == "Moire" ||
      elementName == "Octagon" ||
      elementName == "Oval" ||
      elementName == "RectCenter" ||
      elementName == "RectCham" ||
      elementName == "RectCorner" ||
      elementName == "RectRound" ||
      elementName == "Thermal" ||
      elementName == "Triangle") {
    return StandardShapeFactory().create(elementName);
  }
  else if (elementName == "UserPrimitiveRef" ||
           elementName == "Text" ||
           elementName == "UserSpecial" ||
           elementName == "Arc" ||
           elementName == "Line" ||
           elementName == "Outline" ||
           elementName == "Polyline") {
    return UserShapeFactory().create(elementName);
  }
  throw new InvalidElementError(elementName);
}
