#include "landpattern.h"

void
LandPattern::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Pad") {
        Pad pad;
        pad.initialize(xml);
        m_pads.append(pad);
      }
      else if (xml.name() == "Target") {
        Target target;
        target.initialize(xml);
        m_targets.append(target);
      }
    }
    else if (isEndElementWithName(xml, "LandPattern")) { // </LandPattern>
      return;
    }
  }
}
