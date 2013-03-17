#include "fiducial.h"
#include "utils.h"
#include "standardshapefactory.h"

void
Fiducial::initialize(QXmlStreamReader& xml)
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
        m_location = QPointF(getDoubleAttribute(xml, "Fiducial", "x"),
                             getDoubleAttribute(xml, "Fiducial", "y"));
      }
      else if (isSubstitutionGroupStandardShape(xml.name())) {
        m_standardShape = StandardShapeFactory().create(xml.name());
        if (m_standardShape == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
        m_standardShape->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "Fiducial")) { // </Fiducial>
      return;
    }
  }
}
