#include "textattribute.h"
#include "utils.h"

void
TextAttribute::initialize(QXmlStreamReader& xml)
{
  m_value = getStringAttribute(xml, "TextAttribute", "value");
  QString name = getStringAttribute(xml, "TextAttribute", "name");
  if (name == "bit") {
    m_name = TextAttribute::bit;
  }
  else if (name == "geometry") {
    m_name = TextAttribute::geometry;
  }
  else if (name == "area_name") {
    m_name = TextAttribute::area_name;
  }
  else if (name == "customer") {
    m_name = TextAttribute::customer;
  }
  else if (name == "comment") {
    m_name = TextAttribute::comment;
  }
  else if (name == "technology") {
    m_name = TextAttribute::technology;
  }
  else if (name == "eda_layers") {
    m_name = TextAttribute::eda_layers;
  }
  else {
    errorInvalidAttribute("TextAttribute", "name");
    exit(1);
  }
}
