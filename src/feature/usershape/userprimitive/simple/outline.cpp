#include "outline.h"
#include "linedescgroupfactory.h"
#include "globals.h"

void
Outline::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_lineDescGroup = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Polygon") {
        m_polygon.initialize(xml, units);
      }
      else if (isSubstitutionGroupLineDescGroup(xml.name())) {
        m_lineDescGroup = LineDescGroupFactory().create(xml.name());
        m_lineDescGroup->initialize(xml, units);
      }
    }
    else if (isEndElementWithName(xml, "Outline")) { // </Outline> the end
      if (m_lineDescGroup == NULL) {
        throw new InvalidElementError("Outline");
      }
      break;
    }
  }
}

void
Outline::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  // TODO skipped
  // throw new NonImplementedError("Outline::odbOutputLayerFeature");
}
