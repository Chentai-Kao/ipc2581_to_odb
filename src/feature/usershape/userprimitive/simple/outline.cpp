#include "outline.h"

void
Outline::initialize(QXmlStreamReader& xml)
{
  m_lineDescGroup = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Polygon") {
        m_polygon.initialize(xml);
      }
      else if (xml.name() == "LineDesc") {
        m_lineDescGroup = new LineDesc();
        m_lineDescGroup->initialize(xml);
      }
      else if (xml.name() == "LineDescRef") {
        m_lineDescGroup = new LineDescRef();
        m_lineDescGroup->initialize(xml);
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
