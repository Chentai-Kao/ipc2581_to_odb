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
        m_feature->initialize(xml);
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
    OdbFeatureFile& file,
    QString polarity,
    const Dictionary& dictionary)
{
  QString refId = m_feature->refId();
  Feature *f;
  if (refId == "") { // not a reference to others
    f = m_feature;
  }
  else if (dictionary.entryStandards().contains(refId)) {
    f = dictionary.entryStandards()[refId]; // a reference to standard shape
  }
  else if (dictionary.entryUsers().contains(refId)) {
    f = dictionary.entryUsers()[refId]; // a reference to user shape
  }
  else { // cannot find id in dictionary
    throw new InvalidIdError(refId);
  }

  // call the feature to output
  f->odbOutputLayerFeature(
      file,
      polarity,
      m_location, m_xform);
}
