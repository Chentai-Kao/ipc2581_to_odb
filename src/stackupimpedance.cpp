#include "stackupimpedance.h"

void
StackupImpedance::initialize(QXmlStreamReader& xml)
{
  m_value = getNonNegativeDoubleAttribute(xml, "StackupImpedance", "value");
  m_type = decideStackImpedanceType(
      getStringAttribute(xml, "StackupImpedance", "type"));
  m_tolPlus = getNonNegativeDoubleAttribute(xml, "StackupImpedance", "tolPlus");
  m_tolMinus =
      getNonNegativeDoubleAttribute(xml, "StackupImpedance", "tolMinus");
  m_introduction = getStringAttribute(xml, "StackupImpedance", "introduction");

  m_xform = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Xform") {
        m_xform = new Xform();
        m_xform->initialize(xml);
      }
      else if (xml.name() == "Location") {
        m_location.setX(getDoubleAttribute(xml, "Location", "x"));
        m_location.setY(getDoubleAttribute(xml, "Location", "y"));
      }
      else if (xml.name() == "Polyline") {
        Polyline polyline;
        polyline.initialize(xml);
        m_polylines.append(polyline);
      }
      else if (xml.name() == "Contour") {
        Contour contour;
        contour.initialize(xml);
        m_contours.append(contour);
      }
      else if (xml.name() == "LayerRef") {
        QString layerRef =
            getStringAttribute(xml, "StackupImpedance", "LayerRef");
        m_layerRefs.append(layerRef);
      }
    }
    else if (isEndElementWithName(xml, "StackupImpedance")) {
      return;
    }
  }
}

StackupImpedance::StackImpedanceType
StackupImpedance::decideStackImpedanceType(QString type)
{
  if (type == "MICROSTRIP") {
    return StackupImpedance::MICROSTRIP;
  }
  else if (type == "DIFFERENTIAL_PAIR") {
    return StackupImpedance::DIFFERENTIAL_PAIR;
  }
  else if (type == "EMBEDDED_MICROSTRIP") {
    return StackupImpedance::EMBEDDED_MICROSTRIP;
  }
  else if (type == "EDGE_COUPLED_STRIPLINE") {
    return StackupImpedance::EDGE_COUPLED_STRIPLINE;
  }
  else if (type == "DECOUPLED_EMBEDDED_MICROSTRIP") {
    return StackupImpedance::DECOUPLED_EMBEDDED_MICROSTRIP;
  }
  else if (type == "RAMBUS") {
    return StackupImpedance::RAMBUS;
  }
  else if (type == "COPLANAR_WAVEGUIDE_MICROSTRIP") {
    return StackupImpedance::COPLANAR_WAVEGUIDE_MICROSTRIP;
  }
  else if (type == "COPLANAR_WAVEGUIDE_STRIPLINE") {
    return StackupImpedance::COPLANAR_WAVEGUIDE_STRIPLINE;
  }
  else if (type == "EDGE_COUPLED_COPLANAR_WAVEGUIDE_STRIPLINE") {
    return StackupImpedance::EDGE_COUPLED_COPLANAR_WAVEGUIDE_STRIPLINE;
  }
  else if (type == "EDGE_COUPLED_COPLANAR_WAVEGUIDE_MICROSTRIP") {
    return StackupImpedance::EDGE_COUPLED_COPLANAR_WAVEGUIDE_MICROSTRIP;
  }
  else if (type == "NONE") {
    return StackupImpedance::NONE;
  }
  errorInvalidAttribute("StackupImpedance", "type");
  exit(1);
}
