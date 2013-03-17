#include "slot.h"
#include "simplefactory.h"

void
Slot::initialize(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "Slot", "name");
  QString platingStatus = getStringAttribute(xml, "Slot", "platingStatus");
  if (platingStatus == "PLATED") {
    m_platingStatus = Slot::PLATED;
  }
  else if (platingStatus == "NONPLATED") {
    m_platingStatus = Slot::NONPLATED;
  }
  else if (platingStatus == "VIA") {
    m_platingStatus = Slot::VIA;
  }
  else {
    errorInvalidAttribute("Slot", "platingStatus");
    exit(1);
  }
  m_plusTol = getNonNegativeDoubleAttribute(xml, "Slot", "plusTol");
  m_minusTol = getNonNegativeDoubleAttribute(xml, "Slot", "minusTol");

  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (isSubstitutionGroupSimple(xml.name())) {
        Simple *simple = SimpleFactory().create(xml.name());
        if (simple == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
        simple->initialize(xml);
        m_simples.append(simple);
      }
    }
    else if (isEndElementWithName(xml, "Slot")) { // </Slot>
      return;
    }
  }
}
