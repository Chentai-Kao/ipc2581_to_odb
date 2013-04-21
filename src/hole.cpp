#include "hole.h"
#include "error.h"
#include "circle.h"

void
Hole::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_name = getStringAttribute(xml, "Hole", "name");
  m_diameter = Length(
      getNonNegativeDoubleAttribute(xml, "Hole", "diameter"), units);
  QString platingStatus = getStringAttribute(xml, "Hole", "platingStatus");
  if (platingStatus == "PLATED") {
    m_platingStatus = Hole::PLATED;
  }
  else if (platingStatus == "NONPLATED") {
    m_platingStatus = Hole::NONPLATED;
  }
  else if (platingStatus == "VIA") {
    m_platingStatus = Hole::VIA;
  }
  else {
    throw new InvalidAttributeError("Hole", "platingStatus");
  }
  m_plusTol = getNonNegativeDoubleAttribute(xml, "Hole", "plusTol");
  m_minusTol = getNonNegativeDoubleAttribute(xml, "Hole", "minusTol");
  m_location = QPointF(getDoubleAttribute(xml, "Hole", "x"),
                       getDoubleAttribute(xml, "Hole", "y"));
}

void
Hole::odbOutputLayerFeature(OdbFeatureFile& file, QString polarity)
{
  Circle c(m_diameter);
  c.odbOutputLayerFeature(file, polarity, m_location, NULL);
  file.featuresList().append("\n");
}
