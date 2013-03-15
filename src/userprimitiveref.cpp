#include "userprimitiveref.h"
#include "utils.h"

void
UserPrimitiveRef::initialize(QXmlStreamReader& xml)
{
  m_id = getStringAttribute(xml, "UserPrimitiveRef", "id");
}
