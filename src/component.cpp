#include "component.h"
#include "utils.h"
#include "error.h"

void
Component::initialize(QXmlStreamReader& xml)
{
  // attributes
  m_refDes = getStringAttribute(xml, "Component", "refDes");
  m_packageRef = getStringAttribute(xml, "Component", "packageRef");
  m_part = getStringAttribute(xml, "Component", "part");
  m_layerRef = getStringAttribute(xml, "Component", "layerRef");
  QString mountType = getStringAttribute(xml, "Component", "mountType");
  if (mountType == "SMT") {
    m_mountType = Component::SMT;
  }
  else if (mountType == "THMT") {
    m_mountType = Component::THMT;
  }
  else if (mountType == "OTHER") {
    m_mountType = Component::OTHER;
  }
  else {
    throw new InvalidAttributeError("Component", "mountType");
  }
  m_weight = NULL;
  if (hasAttribute(xml, "weight")) {
    m_weight =
        new qreal(getNonNegativeDoubleAttribute(xml, "Component", "weight"));
  }
  m_height = NULL;
  if (hasAttribute(xml, "height")) {
    m_height =
        new qreal(getNonNegativeDoubleAttribute(xml, "Component", "height"));
  }
  m_standoff = NULL;
  if (hasAttribute(xml, "standoff")) {
    m_standoff =
        new qreal(getNonNegativeDoubleAttribute(xml, "Component", "standoff"));
  }

  // nested elements
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Xform") {
        m_xform = new Xform();
        m_xform->initialize(xml);
      }
      else if (xml.name() == "Location") {
        m_location = QPointF(getDoubleAttribute(xml, "Component", "x"),
                             getDoubleAttribute(xml, "Component", "y"));
      }
    }
    else if (isEndElementWithName(xml, "Component")) { // </Component>
      return;
    }
  }
}
