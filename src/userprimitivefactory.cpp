#include "userprimitivefactory.h"
#include "arc.h"
#include "line.h"
#include "outline.h"
#include "polyline.h"
#include "text.h"
#include "userspecial.h"

UserPrimitive*
UserPrimitiveFactory::create(QXmlStreamReader& xml)
{
  if (xml.name() == "Simple") {
    xml.readNextStartElement();
    if (xml.name() == "Arc") {
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
  }
  else if (xml.name() == "Text") {
    return new Text();
  }
  else if (xml.name() == "UserSpecial") {
    return new UserSpecial();
  }
  return NULL;
}
