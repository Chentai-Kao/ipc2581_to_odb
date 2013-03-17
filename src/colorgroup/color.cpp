#include "color.h"

void
Color::initialize(QXmlStreamReader& xml)
{
  m_r = getIntAttribute(xml, "Color", "r");
  m_g = getIntAttribute(xml, "Color", "g");
  m_b = getIntAttribute(xml, "Color", "b");
  if (m_r < 0 || m_r > 255) {
    errorInvalidAttribute("Color", "r");
    exit(1);
  }
  if (m_g < 0 || m_g > 255) {
    errorInvalidAttribute("Color", "g");
    exit(1);
  }
  if (m_b < 0 || m_b > 255) {
    errorInvalidAttribute("Color", "b");
    exit(1);
  }
}
