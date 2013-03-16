#include "optionattribute.h"
#include "utils.h"

void
OptionAttribute::initialize(QXmlStreamReader& xml)
{
  QString value = getStringAttribute(xml, "OptionAttribute", "value");
  if (value == "Area") {
    m_value = OptionAttribute::Area;
  }
  else if (value == "Bottom") {
    m_value = OptionAttribute::Bottom;
  }
  else if (value == "Buildup") {
    m_value = OptionAttribute::Buildup;
  }
  else if (value == "Core") {
    m_value = OptionAttribute::Core;
  }
  else if (value == "Gerber") {
    m_value = OptionAttribute::Gerber;
  }
  else if (value == "Negative") {
    m_value = OptionAttribute::Negative;
  }
  else if (value == "Other") {
    m_value = OptionAttribute::Other;
  }
  else if (value == "PRESSFIT") {
    m_value = OptionAttribute::PRESSFIT;
  }
  else if (value == "Positive") {
    m_value = OptionAttribute::Positive;
  }
  else if (value == "SMT") {
    m_value = OptionAttribute::SMT;
  }
  else if (value == "THMT") {
    m_value = OptionAttribute::THMT;
  }
  else if (value == "Top") {
    m_value = OptionAttribute::Top;
  }
  else if (value == "detected") {
    m_value = OptionAttribute::detected;
  }
  else if (value == "drilled") {
    m_value = OptionAttribute::drilled;
  }
  else if (value == "full_area") {
    m_value = OptionAttribute::full_area;
  }
  else if (value == "laser") {
    m_value = OptionAttribute::laser;
  }
  else if (value == "non_plated") {
    m_value = OptionAttribute::non_plated;
  }
  else if (value == "non_polarized") {
    m_value = OptionAttribute::non_polarized;
  }
  else if (value == "photo") {
    m_value = OptionAttribute::photo;
  }
  else if (value == "pins_only") {
    m_value = OptionAttribute::pins_only;
  }
  else if (value == "plated") {
    m_value = OptionAttribute::plated;
  }
  else if (value == "polarized") {
    m_value = OptionAttribute::polarized;
  }
  else if (value == "repaired") {
    m_value = OptionAttribute::repaired;
  }
  else if (value == "via") {
    m_value = OptionAttribute::via;
  }
  else {
    errorInvalidAttribute("OptionAttribute", "value");
    exit(1);
  }

  QString name = getStringAttribute(xml, "OptionAttribute", "name");
  if (name == "drill") {
    m_name = OptionAttribute::drill;
  }
  else if (name == "comp") {
    m_name = OptionAttribute::comp;
  }
  else if (name == "layer_hdi_type") {
    m_name = OptionAttribute::layer_hdi_type;
  }
  else {
    errorInvalidAttribute("OptionAttribute", "name");
    exit(1);
  }
}
