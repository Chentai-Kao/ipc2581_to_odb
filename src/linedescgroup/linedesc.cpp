#include "linedesc.h"
#include "utils.h"
#include "error.h"

void
LineDesc::initialize(QXmlStreamReader& xml)
{
  // lineEnd
  QString lineEnd = getStringAttribute(xml, "LineDesc", "lineEnd");
  if (lineEnd == "ROUND") {
    m_lineEnd = LineDesc::ROUND;
  }
  else if (lineEnd == "SQUARE") {
    m_lineEnd = LineDesc::SQUARE;
  }
  else if (lineEnd == "NONE") {
    m_lineEnd = LineDesc::NONE;
  }
  else {
    throw new InvalidAttributeError("LineDesc", "lineEnd");
  }
  // lineWidth
  m_lineWidth = getNonNegativeDoubleAttribute(xml, "LineDesc", "lineWidth");
}
