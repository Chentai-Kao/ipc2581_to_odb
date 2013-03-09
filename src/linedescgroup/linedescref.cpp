#include "linedescref.h"

void
LineDescRef::initialize(QXmlStreamReader& xml)
{
  m_id = getAttribute(xml, "id");
}
