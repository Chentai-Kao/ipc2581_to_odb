#include "stackuplayer.h"
#include "utils.h"

void
StackupLayer::initialize(QXmlStreamReader& xml)
{
  m_layerOrGroupRef =
      getStringAttribute(xml, "StackupLayer", "layerOrGroupRef");
  m_materialType = getStringAttribute(xml, "StackupLayer", "materialType");
  m_thickness = getNonNegativeDoubleAttribute(xml, "StackupLayer", "thickness");
  if (hasAttribute(xml, "weight")) {
    m_weight = getNonNegativeDoubleAttribute(xml, "StackupLayer", "weight");
  }
  if (hasAttribute(xml, "coating")) {
    m_coating = getStringAttribute(xml, "StackupLayer", "coating");
  }
  if (hasAttribute(xml, "comment")) {
    m_comment = getStringAttribute(xml, "StackupLayer", "comment");
  }

  // TODO: skipped non-standard attributes
  // Spec says: "Additional instructions related to the stackup to provide 
  //             information on material restrictions or specifications"
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "StackupLayer")) { // </StackupLayer>
      return;
    }
  }
}
