#include "layerfeature.h"
#include "utils.h"

void
LayerFeature::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_layerRef = getStringAttribute(xml, "LayerFeature", "layerRef");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Set") {
        Set set;
        set.initialize(xml, units);
        m_sets.append(set);
      }
    }
    else if (isEndElementWithName(xml, "LayerFeature")) { // </LayerFeature>
      return;
    }
  }
}

void
LayerFeature::odbOutputLayerFeature(OdbFeatureFile& file, QString layerName)
{
  for (int i = 0; i < m_sets.size(); ++i) {
    m_sets[i].odbOutputLayerFeature(file, layerName);
  }
}
