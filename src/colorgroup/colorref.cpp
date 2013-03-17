#include "colorref.h"
#include "utils.h"

void
ColorRef::initialize(QXmlStreamReader& xml)
{
  m_id = getStringAttribute(xml, "ColorRef", "id");
}
