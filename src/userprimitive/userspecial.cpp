#include "userspecial.h"
#include "featurefactory.h"

void
UserSpecial::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      Feature* feature = FeatureFactory().create(xml);
      if (feature == NULL) {
        errorInvalidAttribute("UserSpecial", "");
        exit(1);
      }
      feature->initialize(xml);
      // append to the feature list
      m_features.append(feature);
    }
    else if (isEndElementWithName(xml, "UserSpecial")) {
      break;
    }
  }
  qDebug() << m_features.size();
}
