#include "featuresgroup.h"
#include "featurefactory.h"
#include "error.h"

void
Features::initialize(QXmlStreamReader& xml)
{
  m_xform = NULL;
  m_feature = NULL;
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
      else if (isSubstitutionGroupFeature(xml.name())) {
        m_feature = FeatureFactory().create(xml.name());
      }
    }
    else if (isEndElementWithName(xml, "Features")) { // </Features>
      if (m_feature == NULL) {
        throw new InvalidElementError("Features");
      }
      return;
    }
  }
}

void
Features::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    const QHash<QString, StandardPrimitive*>& entryStandards,
    const QHash<QString, UserPrimitive*>& entryUsers)
{
  QString refId = m_feature->refId();
  Feature *f;
  if (refId == "") { // not a reference to others
    f = m_feature;
  }
  else if (entryStandards.contains(refId)) { // a reference to standard shape
    f = entryStandards[refId];
  }
  else if (entryUsers.contains(refId)) { // a reference to user shape
    f = entryUsers[refId];
  }
  else { // cannot find id in dictionary
    throw new InvalidIdError(refId);
  }

  // call the feature to output
  f->odbOutputLayerFeature(
      symbolsTable, attributeTable, attributeTexts, featuresList, polarity,
      m_location, m_xform);
}
