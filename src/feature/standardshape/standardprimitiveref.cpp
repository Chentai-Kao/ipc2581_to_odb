#include "standardprimitiveref.h"
#include "utils.h"

void
StandardPrimitiveRef::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_id = getStringAttribute(xml, "StandardPrimitiveRef", "id");
}
