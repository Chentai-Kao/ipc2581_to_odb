#include "colorref.h"

void
ColorRef::initialize(QXmlStreamReader& xml)
{
  m_id = getAttribute(xml, "id");
}
