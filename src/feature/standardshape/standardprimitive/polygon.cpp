#include "polygon.h"
#include "utils.h"
#include "polystepfactory.h"

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
      else if (isSubstitutionGroupPolyStep(xml.name())) {
        PolyStep *p = PolyStepFactory().create(xml.name());
        if (p == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
        p->initialize(xml);
        m_polySteps.append(p);
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
