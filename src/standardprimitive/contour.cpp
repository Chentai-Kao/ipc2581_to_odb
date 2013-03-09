#include "contour.h"

void
Contour::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "Polygon")) {
      m_polygon.initialize(xml);
    }
    else if (isStartElementWithName(xml, "Cutout")) {
      Polygon polygon;
      polygon.initialize(xml);
      m_cutout.append(polygon);
    }
    else if (isEndElementWithName(xml, "Contour")) { // </Contour> the end
      return;
    }
  }
}
