#include "featuresgroup.h"
#include "featurefactory.h"
#include "error.h"
#include "globals.h"

void
Features::initialize(QXmlStreamReader& xml, UnitsType units)
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
        m_location = QPointF(
            toInch(getDoubleAttribute(xml, "Location", "x"), units),
            toInch(getDoubleAttribute(xml, "Location", "y"), units));
      }
      else if (isSubstitutionGroupFeature(xml.name())) {
        m_feature = FeatureFactory().create(xml.name());
        m_feature->initialize(xml, units);
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
Features::odbOutputLayerFeature(OdbFeatureFile& file, QString polarity)
{
  QString refId = m_feature->refId();
  Feature *f;
  if (refId == "") { // not a reference to others
    f = m_feature;
  }
  else if (g_entryStandards.contains(refId)) { // a reference to standard shape
    f = g_entryStandards[refId];
  }
  else if (g_entryUsers.contains(refId)) { // a reference to user shape
    f = g_entryUsers[refId];
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
