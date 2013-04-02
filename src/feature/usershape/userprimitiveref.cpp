#include "userprimitiveref.h"
#include "utils.h"

void
UserPrimitiveRef::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_id = getStringAttribute(xml, "UserPrimitiveRef", "id");
}
