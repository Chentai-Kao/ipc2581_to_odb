#include "steprepeat.h"
#include "utils.h"

void
StepRepeat::initialize(QXmlStreamReader& xml)
{
  m_stepRef = getStringAttribute(xml, "StepRepeat", "stepRef");
  m_x = getDoubleAttribute(xml, "StepRepeat", "x");
  m_y = getDoubleAttribute(xml, "StepRepeat", "y");
  m_nx = getNonNegativeIntAttribute(xml, "StepRepeat", "nx");
  m_ny = getNonNegativeIntAttribute(xml, "StepRepeat", "ny");
  m_dx = getNonNegativeDoubleAttribute(xml, "StepRepeat", "dx");
  m_dy = getNonNegativeDoubleAttribute(xml, "StepRepeat", "dy");
  m_angle = getDoubleAttribute(xml, "StepRepeat", "angle");
  m_mirror = getBoolAttribute(xml, "mirror");
}
