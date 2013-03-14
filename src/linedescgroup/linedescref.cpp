#include "linedescref.h"

void
LineDescRef::initialize(QXmlStreamReader& xml)
{
  m_id = getStringAttribute(xml, "LineDescRef", "id");
}
