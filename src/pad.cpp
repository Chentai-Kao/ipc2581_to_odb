#include "pad.h"
#include "standardshapefactory.h"

void
Pad::initialize(QXmlStreamReader& xml)
{
  m_xform = NULL;
  m_pinRef = NULL;
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
        if (m_standardShape == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "PinRef") {
        m_pinRef = new PinRef();
        m_pinRef->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "Pad")) { // </Pad>
      return;
    }
  }
}
