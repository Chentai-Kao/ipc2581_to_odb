#include "logicalnet.h"
#include "utils.h"

void
LogicalNet::initialize(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "LogicalNet", "name");
  m_netClass = decideNetClassType(xml);
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Attribute") {
        // TODO skipped
      }
      else if (xml.name() == "PinRef") {
        PinRef pinRef;
        pinRef.initialize(xml);
        m_pinRefs.append(pinRef);
      }
    }
    else if (isEndElementWithName(xml, "LogicalNet")) { // </LogicalNet>
      return;
    }
  }
}

LogicalNet::NetClassType
LogicalNet::decideNetClassType(QXmlStreamReader& xml)
{
  QString netClass = getStringAttribute(xml, "LogicalNet", "NetClass");
  if (netClass == "CLK") {
    return LogicalNet::CLK;
  }
  else if (netClass == "FIXED") {
    return LogicalNet::FIXED;
  }
  else if (netClass == "GROUND") {
    return LogicalNet::GROUND;
  }
  else if (netClass == "SIGNAL") {
    return LogicalNet::SIGNAL;
  }
  else if (netClass == "POWER") {
    return LogicalNet::POWER;
  }
  return LogicalNet::UNUSED;
}
