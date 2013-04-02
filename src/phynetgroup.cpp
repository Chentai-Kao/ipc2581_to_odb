#include "phynetgroup.h"
#include "utils.h"
#include "phynet.h"

void
PhyNetGroup::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_name = getStringAttribute(xml, "PhyNetGroup", "name");
  m_optimized = getBoolAttribute(xml, "optimized");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "PhyNet") {
        PhyNet phyNet;
        phyNet.initialize(xml, units);
        m_phyNets.append(phyNet);
      }
    }
    else if (isEndElementWithName(xml, "PhyNetGroup")) { // </PhyNetGroup>
      return;
    }
  }
}
