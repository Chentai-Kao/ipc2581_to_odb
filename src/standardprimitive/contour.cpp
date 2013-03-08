#include "contour.h"

void
Contour::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "Polygon")) {
      m_polygon = polygonGen(xml, "Polygon");
    }
    else if (isStartElementWithName(xml, "Cutout")) {
      m_cutout.append(polygonGen(xml, "Cutout"));
    }
    else if (isEndElementWithName(xml, "Contour")) { // </Contour> the end
      return;
    }
  }
}

ContourPolygon
Contour::polygonGen(QXmlStreamReader& xml, QString elementName)
{
  ContourPolygon polygon;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "PolyBegin") {
        // <PolyBegin>
        polygon.m_polyBegin.rx() = getDoubleAttribute(xml, "PolyBegin", "x");
        polygon.m_polyBegin.ry() = getDoubleAttribute(xml, "PolyBegin", "y");
      }
      else if (xml.name() == "PolyStepCurve") {
        // <PolyStepCurve>
        PolyStep *polyStep = new PolyStepCurve(
            getDoubleAttribute(xml, "PolyStepCurve", "x"),
            getDoubleAttribute(xml, "PolyStepCurve", "y"),
            getDoubleAttribute(xml, "PolyStepCurve", "centerX"),
            getDoubleAttribute(xml, "PolyStepCurve", "centerY"));
        // clockwise or not
        if (xml.attributes().hasAttribute("clockwise")) {
          polyStep->setClockwise(getBoolAttribute(xml, "clockwise"));
        }
        // append to polyStep list of the polygon
        polygon.m_polySteps.append(polyStep);
      }
      else if (xml.name() == "PolyStepSegment") {
        // <PolyStepSegment>
        PolyStep *polyStep = new PolyStepSegment(
            getDoubleAttribute(xml, "PolyStepSegment", "x"),
            getDoubleAttribute(xml, "PolyStepSegment", "y"));
        // append to polyStep list of the polygon
        polygon.m_polySteps.append(polyStep);
      }
    }
    else if (isEndElementWithName(xml, elementName)) { // </Contour> the end
      break;
    }
  }
  if (!isClosedShape(polygon)) {
    errorInvalidAttribute("Contour", "Polygon");
    exit(1);
  }
  return polygon;
}

bool
Contour::isClosedShape(const ContourPolygon& polygon)
{
  return (polygon.m_polyBegin.x() == polygon.m_polySteps.last()->m_point.x() &&
          polygon.m_polyBegin.y() == polygon.m_polySteps.last()->m_point.y());
}
