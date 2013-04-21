#include "hole.h"
#include "utils.h"
#include "error.h"

void
Hole::initialize(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "Hole", "name");
  m_diameter = getNonNegativeDoubleAttribute(xml, "Hole", "diameter");
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
#if 0
  // if the shape is a reference, find it in the list
  QString refId = m_standardShape->refId();
  StandardShape *s;
  if (refId == "") {
    s = m_standardShape;
  }
  else if (g_entryStandards.contains(refId)) {
    s = g_entryStandards[refId];
  }
  else {
    throw new InvalidIdError(refId);
  }

  // find the layer by name
  int layerIdx;
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].name() == layerName) {
      layerIdx = i;
      break;
    }
  }

  // call the shape to output
  s->odbOutputLayerFeature(file, polarity, m_location, m_xform);
  file.featuresList().append("\n");
#endif
}
