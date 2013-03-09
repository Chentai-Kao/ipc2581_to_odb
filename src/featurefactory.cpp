#include "featurefactory.h"
// from standard primitive
#include "butterfly.h"
#include "circle.h"
#include "contour.h"
#include "diamond.h"
#include "donut.h"
#include "ellipse.h"
#include "hexagon.h"
#include "moire.h"
#include "octagon.h"
#include "oval.h"
#include "rectcenter.h"
#include "rectcham.h"
#include "rectcorner.h"
#include "rectround.h"
#include "thermal.h"
#include "triangle.h"
// from user primitive
#include "arc.h"
#include "line.h"
#include "outline.h"
#include "polyline.h"

Feature*
FeatureFactory::create(QXmlStreamReader& xml)
{
  if (xml.name() == "Butterfly") {
    return new Butterfly();
  }
  else if (xml.name() == "Circle") {
    return new Circle();
  }
  else if (xml.name() == "Contour") {
    return new Contour();
  }
  else if (xml.name() == "Diamond") {
    return new Diamond();
  }
  else if (xml.name() == "Donut") {
    return new Donut();
  }
  else if (xml.name() == "Ellipse") {
    return new Ellipse();
  }
  else if (xml.name() == "Hexagon") {
    return new Hexagon();
  }
  else if (xml.name() == "Moire") {
    return new Moire();
  }
  else if (xml.name() == "Octagon") {
    return new Octagon();
  }
  else if (xml.name() == "Oval") {
    return new Oval();
  }
  else if (xml.name() == "RectCenter") {
    return new RectCenter();
  }
  else if (xml.name() == "RectCham") {
    return new RectCham();
  }
  else if (xml.name() == "RectCorner") {
    return new RectCorner();
  }
  else if (xml.name() == "RectRound") {
    return new RectRound();
  }
  else if (xml.name() == "Thermal") {
    return new Thermal();
  }
  else if (xml.name() == "Triangle") {
    return new Triangle();
  }
  else if (xml.name() == "Arc") {
    return new Arc();
  }
  else if (xml.name() == "Line") {
    return new Line();
  }
  else if (xml.name() == "Outline") {
    return new Outline();
  }
  else if (xml.name() == "Polyline") {
    return new Polyline();
  }

  return NULL;
}
