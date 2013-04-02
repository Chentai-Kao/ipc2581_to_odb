#include "fiducial.h"
#include "utils.h"
#include "standardshapefactory.h"

void
Fiducial::initialize(QXmlStreamReader& xml, UnitsType units)
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
        m_standardShape->initialize(xml, units);
      }
    }
    else if (isEndElementWithName(xml, "Fiducial")) { // </Fiducial>
      return;
    }
  }
}
