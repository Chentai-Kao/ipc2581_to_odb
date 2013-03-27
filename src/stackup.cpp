#include "stackup.h"
#include "error.h"

void
Stackup::initialize(QXmlStreamReader& xml)
{
  m_overallThickness =
      getNonNegativeDoubleAttribute(xml, "Stackup", "overallThickness");
  m_tolPlus = getNonNegativeDoubleAttribute(xml, "Stackup", "tolPlus");
  m_tolMinus = getNonNegativeDoubleAttribute(xml, "Stackup", "tolMinus");
  QString whereMeasured = getStringAttribute(xml, "Stackup", "whereMeasured");
  if (whereMeasured == "LAMINATE") {
    m_whereMeasured = Stackup::LAMINATE;
  }
  else if (whereMeasured == "METAL") {
    m_whereMeasured = Stackup::METAL;
  }
  else if (whereMeasured == "MASK") {
    m_whereMeasured = Stackup::MASK;
  }
  else if (whereMeasured == "OTHER") {
    m_whereMeasured = Stackup::OTHER;
  }
  else {
    throw new InvalidAttributeError("Stackup", "whereMeasured");
  }

  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "StackupGroup") {
        StackupGroup stackupGroup;
        stackupGroup.initialize(xml);
        m_stackupGroups.append(stackupGroup);
      }
      else if (xml.name() == "StackupImpedance") {
        StackupImpedance stackupImpedance;
        stackupImpedance.initialize(xml);
        m_stackupImpedances.append(stackupImpedance);
      }
    }
    else if (isEndElementWithName(xml, "Stackup")) { // </Stackup>
      return;
    }
  }
}
