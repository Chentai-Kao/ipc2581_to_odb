#include "simplefactory.h"
#include "error.h"
#include "arc.h"
#include "line.h"
#include "outline.h"
#include "polyline.h"

Simple*
SimpleFactory::create(QStringRef elementName)
{
  if (elementName == "Arc") {
    return new Arc();
  }
  else if (elementName == "Line") {
    return new Line();
  }
  else if (elementName == "Outline") {
    return new Outline();
  }
  else if (elementName == "Polyline") {
    return new Polyline();
  }
  throw new InvalidElementError(elementName);
}
