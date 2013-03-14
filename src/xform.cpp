#include "xform.h"
#include "utils.h"

void
Xform::initialize(QXmlStreamReader& xml)
{
  m_offset = QPointF(0.0, 0.0);
  if (hasAttribute(xml, "xOffset")) {
    m_offset.setX(getDoubleAttribute(xml, "Xform", "xOffset"));
  }
  if (hasAttribute(xml, "yOffset")) {
    m_offset.setY(getDoubleAttribute(xml, "Xform", "yOffset"));
  }
  m_rotation = 0.0;
  if (hasAttribute(xml, "rotation")) {
    m_rotation = getNonNegativeDoubleAttribute(xml, "Xform", "rotation");
  }
  m_mirror = false;
  if (hasAttribute(xml, "mirror")) {
    m_mirror = getBoolAttribute(xml, "mirror");
  }
  m_scale = 1.0;
  if (hasAttribute(xml, "scale")) {
    m_scale = getNonNegativeDoubleAttribute(xml, "Xform", "scale");
  }
}
