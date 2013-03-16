#include "polygon.h"

void
Polygon::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "PolyBegin") {
        m_polyBegin.rx() = getDoubleAttribute(xml, "PolyBegin", "x");
        m_polyBegin.ry() = getDoubleAttribute(xml, "PolyBegin", "y");
      }
      else if (xml.name() == "PolyStepCurve") {
        PolyStep *polyStep = new PolyStepCurve();
        polyStep->initialize(xml);
        m_polySteps.append(polyStep);
      }
      else if (xml.name() == "PolyStepSegment") {
        PolyStep *polyStep = new PolyStepSegment();
        polyStep->initialize(xml);
        m_polySteps.append(polyStep);
      }
    }
    else if (isEndElementWithName(xml, "Polygon") || // </Polygon> the end
             isEndElementWithName(xml, "Cutout")) { // another possible name
      break;
    }
  }
  if (!isClosedShape()) {
    errorInvalidAttribute("Polygon", "");
    exit(1);
  }
}

bool
Polygon::isClosedShape()
{
  return (m_polyBegin.x() == m_polySteps.last()->point().x() &&
          m_polyBegin.y() == m_polySteps.last()->point().y());
}
