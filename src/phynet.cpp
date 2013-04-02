#include "phynet.h"
#include "utils.h"
#include "phynetpoint.h"

void
PhyNet::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_name = getStringAttribute(xml, "PhyNet", "name");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "PhyNetPoint") {
        PhyNetPoint phyNetPoint;
        phyNetPoint.initialize(xml, units);
        m_phyNetPoints.append(phyNetPoint);
      }
    }
    else if (isEndElementWithName(xml, "PhyNet")) { // </PhyNet>
      return;
    }
  }
}
