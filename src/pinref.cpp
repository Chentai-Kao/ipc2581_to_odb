#include "pinref.h"
#include "utils.h"

void
PinRef::initialize(QXmlStreamReader& xml)
{
  m_componentRef = NULL;
  if (hasAttribute(xml, "componentRef")) {
    m_componentRef =
        new QString(getStringAttribute(xml, "PinRef", "componentRef"));
  }
  m_pin = getStringAttribute(xml, "PinRef", "pin");
  m_title = NULL;
  if (hasAttribute(xml, "title")) {
    m_title = new QString(getStringAttribute(xml, "PinRef", "title"));
  }
}
