#include "target.h"
#include "standardshapefactory.h"

void
Target::initialize(QXmlStreamReader& xml)
{
  m_xform = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Xform") {
        m_xform = new Xform();
        m_xform->initialize(xml);
      }
      else if (xml.name() == "Location") {
        m_location = QPointF(getDoubleAttribute(xml, "Location", "x"),
                             getDoubleAttribute(xml, "Location", "y"));
      }
      else if (isSubstitutionGroupStandardShape(xml.name())) {
        m_standardShape = StandardShapeFactory().create(xml.name());
        m_standardShape->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "Target")) { // </Target>
      return;
    }
  }
}
