#include "doubleattribute.h"
#include "utils.h"

void
DoubleAttribute::initialize(QXmlStreamReader& xml)
{
  m_value = getDoubleAttribute(xml, "DoubleAttribute", "value");
  QString name = getStringAttribute(xml, "DoubleAttribute", "name");
  if (name == "pitch") {
    m_name = DoubleAttribute::pitch;
  }
  else if (name == "board_thickness") {
    m_name = DoubleAttribute::board_thickness;
  }
  else if (name == "layer_dielectric") {
    m_name = DoubleAttribute::layer_dielectric;
  }
  else {
    errorInvalidAttribute("DoubleAttribute", "name");
    exit(1);
  }
}
