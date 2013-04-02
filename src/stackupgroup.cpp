#include "stackupgroup.h"
#include "utils.h"

void
StackupGroup::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_name = getStringAttribute(xml, "StackupGroup", "name");
  m_thickness = getNonNegativeDoubleAttribute(xml, "StackupGroup", "thickness");
  m_tolPlus = getNonNegativeDoubleAttribute(xml, "StackupGroup", "tolPlus");
  m_tolMinus = getNonNegativeDoubleAttribute(xml, "StackupGroup", "tolMinus");
  
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "StackupLayer") {
        StackupLayer stackupLayer;
        stackupLayer.initialize(xml);
        m_stackupLayers.append(stackupLayer);
      }
    }
    else if (isEndElementWithName(xml, "StackupGroup")) { // </StackupGroup>
      return;
    }
  }
}
