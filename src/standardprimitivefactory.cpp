#include "standardprimitivefactory.h"

StandardPrimitive*
StandardPrimitiveFactory::create(QStringRef elementName)
{
  if (elementName == "Butterfly") {
    return new SpButterfly();
  }
  else if (elementName == "Circle") {
    return new SpCircle();
  }
  else if (elementName == "Contour") {
    return new SpContour();
  }
  else if (elementName == "Diamond") {
    return new SpDiamond();
  }
  else if (elementName == "Donut") {
    return new SpDonut();
  }
  else if (elementName == "Ellipse") {
    return new SpEllipse();
  }
  else if (elementName == "Hexagon") {
    return new SpHexagon();
  }
  else if (elementName == "Moire") {
    return new SpMoire();
  }
  else if (elementName == "Octagon") {
    return new SpOctagon();
  }
  else if (elementName == "Oval") {
    return new SpOval();
  }
  else if (elementName == "RectCenter") {
    return new SpRectCenter();
  }
  else if (elementName == "RectCham") {
    return new SpRectCham();
  }
  else if (elementName == "RectCorner") {
    return new SpRectCorner();
  }
  else if (elementName == "RectRound") {
    return new SpRectRound();
  }
  else if (elementName == "Thermal") {
    return new SpThermal();
  }
  else if (elementName == "Triangle") {
    return new SpTriangle();
  }

  return NULL;
}
