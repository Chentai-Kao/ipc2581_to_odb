#include "linedescref.h"
#include "utils.h"

void
LineDescRef::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_id = getStringAttribute(xml, "LineDescRef", "id");
}
