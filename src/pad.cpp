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

void
Pad::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    const QHash<QString, StandardPrimitive*>& entryStandards)
{
  QString refId = m_standardShape->refId();
  if (refId != "") { // it is <standardPrimitiveRef>, call the reference
    entryStandards[refId]->odbOutputLayerFeature(
        symbolsTable, attributeTable, attributeTexts, featuresList, polarity,
        m_location, m_xform);
  }
  else { // it is a normal feature
    m_standardShape->odbOutputLayerFeature(
        symbolsTable, attributeTable, attributeTexts, featuresList, polarity,
        m_location, m_xform);
  }
}
