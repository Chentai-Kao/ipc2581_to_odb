#include "step.h"
#include "utils.h"

void
Step::initialize(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "Step", "name");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Datum") {
        m_datum = QPointF(getDoubleAttribute(xml, "Step", "x"),
                          getDoubleAttribute(xml, "Step", "y"));
      }
      else if (xml.name() == "Profile") {
        m_profile.initialize(xml);
      }
      else if (xml.name() == "Package") {
        Package package;
        package.initialize(xml);
        m_packages.append(package);
      }
      else if (xml.name() == "Component") {
        Component component;
        component.initialize(xml);
        m_components.append(component);
      }
    }
    else if (isEndElementWithName(xml, "Step")) { // </Step>
      return;
    }
  }
}
