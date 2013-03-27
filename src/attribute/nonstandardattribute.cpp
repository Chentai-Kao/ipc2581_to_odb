#include "nonstandardattribute.h"
#include "utils.h"
#include "error.h"

void
NonstandardAttribute::initialize(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "NonstandardAttribute", "name");
  m_value = getStringAttribute(xml, "NonstandardAttribute", "value");
  QString type = getStringAttribute(xml, "NonstandardAttribute", "type");
  if (type == "DOUBLE") {
    m_type = NonstandardAttribute::DOUBLE;
  }
  else if (type == "INTEGER") {
    m_type = NonstandardAttribute::INTEGER;
  }
  else if (type == "BOOLEAN") {
    m_type = NonstandardAttribute::BOOLEAN;
  }
  else if (type == "STRING") {
    m_type = NonstandardAttribute::STRING;
  }
  else {
    throw new InvalidAttributeError("NonstandardAttribute", "type");
  }
}
