#include "layerfeature.h"
#include "utils.h"

void
LayerFeature::initialize(QXmlStreamReader& xml)
{
  m_layerRef = getStringAttribute(xml, "LayerFeature", "layerRef");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Set") {
        Set set;
        set.initialize(xml);
        m_sets.append(set);
      }
    }
    else if (isEndElementWithName(xml, "LayerFeature")) { // </LayerFeature>
      return;
    }
  }
}
