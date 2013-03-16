#include "integerattribute.h"
#include "utils.h"

void
IntegerAttribute::initialize(QXmlStreamReader& xml)
{
  m_value = getIntAttribute(xml, "IntegerAttribute", "value");
  QString name = getStringAttribute(xml, "IntegerAttribute", "name");
  if (name == "cut_line") {
    m_name = IntegerAttribute::cut_line;
  }
  else if (name == "design_origin_x") {
    m_name = IntegerAttribute::design_origin_x;
  }
  else if (name == "design_origin_y") {
    m_name = IntegerAttribute::design_origin_y;
  }
  else if (name == "num_local_fiducials") {
    m_name = IntegerAttribute::num_local_fiducials;
  }
  else if (name == "pilot_hole") {
    m_name = IntegerAttribute::pilot_hole;
  }
  else if (name == "testpoint_count") {
    m_name = IntegerAttribute::testpoint_count;
  }
  else {
    errorInvalidAttribute("IntegerAttribute", "name");
    exit(1);
  }
}
