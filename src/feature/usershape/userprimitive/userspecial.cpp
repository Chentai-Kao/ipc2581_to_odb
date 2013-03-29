#include "userspecial.h"
#include "featurefactory.h"

void
UserSpecial::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      Feature* f = FeatureFactory().create(xml.name());
      f->initialize(xml);
      // append to the feature list
      m_features.append(f);
    }
    else if (isEndElementWithName(xml, "UserSpecial")) {
      break;
    }
  }
}

void
UserSpecial::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  // TODO skipped
  // throw new NonImplementedError("UserSpecial::odbOutputLayerFeatre");
}
