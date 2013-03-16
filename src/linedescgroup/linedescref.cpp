#include "linedescref.h"
#include "utils.h"

void
LineDescRef::initialize(QXmlStreamReader& xml)
{
  m_id = getStringAttribute(xml, "LineDescRef", "id");
}
