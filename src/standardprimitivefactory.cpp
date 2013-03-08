#include "standardprimitivefactory.h"

StandardPrimitive*
StandardPrimitiveFactory::create(QStringRef elementName)
{
  if (elementName == "Butterfly") {
    return new Butterfly();
  }
  else if (elementName == "Circle") {
    return new Circle();
  }
  else if (elementName == "Contour") {
    return new Contour();
  }
  else if (elementName == "Diamond") {
    return new Diamond();
  }
  else if (elementName == "Donut") {
    return new Donut();
  }
  else if (elementName == "Ellipse") {
    return new Ellipse();
  }
  else if (elementName == "Hexagon") {
    return new Hexagon();
  }
  else if (elementName == "Moire") {
    return new Moire();
  }
  else if (elementName == "Octagon") {
    return new Octagon();
  }
  else if (elementName == "Oval") {
    return new Oval();
  }
  else if (elementName == "RectCenter") {
    return new RectCenter();
  }
  else if (elementName == "RectCham") {
    return new RectCham();
  }
  else if (elementName == "RectCorner") {
    return new RectCorner();
  }
  else if (elementName == "RectRound") {
    return new RectRound();
  }
  else if (elementName == "Thermal") {
    return new Thermal();
  }
  else if (elementName == "Triangle") {
    return new Triangle();
  }

  return NULL;
}
