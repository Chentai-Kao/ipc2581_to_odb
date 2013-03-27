#include "standardshapefactory.h"
#include "standardprimitivefactory.h"
#include "standardprimitiveref.h"
#include "error.h"

StandardShape*
StandardShapeFactory::create(QStringRef elementName)
{
  if (elementName == "StandardPrimitiveRef") {
    return new StandardPrimitiveRef();
  }
  else if (elementName == "Butterfly" ||
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
    return StandardPrimitiveFactory().create(elementName);
  }
  throw new InvalidElementError(elementName);
}
