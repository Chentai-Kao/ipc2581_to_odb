#include "stackuplayer.h"
#include "utils.h"
#include "attribute.h"
#include "booleanattribute.h"
#include "doubleattribute.h"
#include "integerattribute.h"
#include "nonstandardattribute.h"
#include "optionattribute.h"
#include "textattribute.h"

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
      if (xml.name() == "BooleanAttribute") {
        Attribute *attribute = new BooleanAttribute();
        attribute->initialize(xml);
        m_attributes.append(attribute);
      }
      else if (xml.name() == "DoubleAttribute") {
        Attribute *attribute = new DoubleAttribute();
        attribute->initialize(xml);
        m_attributes.append(attribute);
      }
      else if (xml.name() == "IntegerAttribute") {
        Attribute *attribute = new IntegerAttribute();
        attribute->initialize(xml);
        m_attributes.append(attribute);
      }
      else if (xml.name() == "NonstandardAttribute") {
        Attribute *attribute = new NonstandardAttribute();
        attribute->initialize(xml);
        m_attributes.append(attribute);
      }
      else if (xml.name() == "OptionAttribute") {
        Attribute *attribute = new OptionAttribute();
        attribute->initialize(xml);
        m_attributes.append(attribute);
      }
      else if (xml.name() == "TextAttribute") {
        Attribute *attribute = new TextAttribute();
        attribute->initialize(xml);
        m_attributes.append(attribute);
      }
    }
    else if (isEndElementWithName(xml, "StackupLayer")) { // </StackupLayer>
      return;
    }
  }
}
