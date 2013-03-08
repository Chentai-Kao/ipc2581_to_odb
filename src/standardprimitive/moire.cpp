#include "moire.h"

void
Moire::initialize(QXmlStreamReader& xml)
{
  // required attributes
  m_diameter = getNonNegativeDoubleAttribute(xml, "Moire", "diameter");
  m_ringWidth = getNonNegativeDoubleAttribute(xml, "Moire", "ringWidth");
  m_ringGap = getNonNegativeDoubleAttribute(xml, "Moire", "ringGap");
  m_ringGap = getNonNegativeDoubleAttribute(xml, "Moire", "ringGap");
  m_ringNumber = getNonNegativeIntAttribute(xml, "Moire", "ringNumber");
  // optional attributes
  if (xml.attributes().hasAttribute("lineWidth")) {
    m_lineWidth = getNonNegativeDoubleAttribute(xml, "Moire", "lineWidth");
  }
  if (xml.attributes().hasAttribute("lineLength")) {
    m_lineLength = getNonNegativeDoubleAttribute(xml, "Moire", "lineLength");
  }
  if (xml.attributes().hasAttribute("lineAngle")) {
    m_lineAngle = getNonNegativeDoubleAttribute(xml, "Moire", "lineAngle");
    if (m_lineAngle < 0 || m_lineAngle > 90) {
      errorInvalidAttribute("Moire", "lineAngle");
      exit(1);
    }
  }
}
