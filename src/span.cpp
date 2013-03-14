#include "span.h"
#include "utils.h"

void
Span::initialize(QXmlStreamReader& xml)
{
  if (hasAttribute(xml, "fromLayer")) {
    m_fromLayer = getStringAttribute(xml, "Span", "fromLayer");
  }
  if (hasAttribute(xml, "toLayer")) {
    m_toLayer = getStringAttribute(xml, "Span", "toLayer");
  }
}
