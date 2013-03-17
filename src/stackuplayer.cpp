#include "stackuplayer.h"
#include "utils.h"
#include "attributefactory.h"

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

  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (isSubstitutionGroupAttribute(xml.name())) {
        Attribute *a = AttributeFactory().create(xml.name());
        a->initialize(xml);
        m_attributes.append(a);
      }
    }
    else if (isEndElementWithName(xml, "StackupLayer")) { // </StackupLayer>
      return;
    }
  }
}
