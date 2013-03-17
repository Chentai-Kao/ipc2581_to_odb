#include "contour.h"

void
Contour::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Polygon") {
        m_polygon.initialize(xml);
      }
      else if (xml.name() == "Cutout") {
        Polygon polygon;
        polygon.initialize(xml);
        m_cutouts.append(polygon);
      }
    }
    else if (isEndElementWithName(xml, "Contour") || // </Contour> the end
             isEndElementWithName(xml, "Profile")) { // other possible name
      return;
    }
  }
}
