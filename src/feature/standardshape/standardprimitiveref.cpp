#include "standardprimitiveref.h"
#include "utils.h"

void
StandardPrimitiveRef::initialize(QXmlStreamReader& xml)
{
  m_id = getStringAttribute(xml, "StandardPrimitiveRef", "id");
}
