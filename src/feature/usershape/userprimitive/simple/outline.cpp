#include "outline.h"

void
Outline::initialize(QXmlStreamReader& xml)
{
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
      break;
    }
  }
}

void
Outline::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    QPointF location, Xform *xform)
{
  // TODO skipped
  // throw new NonImplementedError("Outline::odbOutputLayerFeature");
}
