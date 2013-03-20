#include "layer.h"

void
Layer::initialize(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "Layer", "name");
  m_layerFunction =
      decideLayerFunction(getStringAttribute(xml, "Layer", "layerFunction"));
  m_side = decideSide(getStringAttribute(xml, "Layer", "side"));
  QString polarity = getStringAttribute(xml, "Layer", "polarity");
  if (polarity == "NEGATIVE") {
    m_polarity = Layer::NEGATIVE;
  }
  else {
    m_polarity = Layer::POSITIVE;
  }

  m_span = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Span") {
        m_span = new Span();
        m_span->initialize(xml);
      }
      else if (xml.name() == "DrillTool") {
        DrillTool drillTool;
        drillTool.initialize(xml);
        m_drillTools.append(drillTool);
      }
    }
    else if (isEndElementWithName(xml, "Layer")) { // </Layer>
      return;
    }
  }
}

QString
Layer::context()
{
  if (m_layerFunction == COURTYARD ||
      m_layerFunction == GRAPHIC ||
      m_layerFunction == DOCUMENT ||
      m_layerFunction == LANDPATTERN ||
      m_layerFunction == COMPONENT_TOP ||
      m_layerFunction == COMPONENT_BOTTOM ||
      m_layerFunction == BOARD_OUTLINE ||
      m_layerFunction == OTHER) {
    return "MISC";
  }
  return "BOARD";
}

QString
Layer::type()
{
  switch (m_layerFunction) {
    case PLANE :
      return "POWER_GROUND";
    case MIXED :
      return "MIXED";
    case SOLDERMASK :
      return "SOLDER_MASK";
    case SOLDERPASTE :
    case PASTEMASK :
      return "SOLDER_PASTE";
    case SILKSCREEN :
      return "SILK_SCREEN";
    case DRILL :
      return "DRILL";
    case ROUTE :
      return "ROUT";
    case DOCUMENT :
      return "DOCUMENT";
    case COMPONENT_TOP :
    case COMPONENT_BOTTOM :
      return "COMPONENT";
    default :
      return "SIGNAL";
  }
}

Layer::LayerFunctionType
Layer::decideLayerFunction(const QString layerFunctionStr)
{
  if (layerFunctionStr == "ASSEMBLY") {
    return Layer::ASSEMBLY;
  }
  else if (layerFunctionStr == "BOARD_OUTLINE") {
    return Layer::BOARD_OUTLINE;
  }
  else if (layerFunctionStr == "CAPACITIVE") {
    return Layer::CAPACITIVE;
  }
  else if (layerFunctionStr == "COATINGCOND") {
    return Layer::COATINGCOND;
  }
  else if (layerFunctionStr == "COATINGNONCOND") {
    return Layer::COATINGNONCOND;
  }
  else if (layerFunctionStr == "COMPONENT_BOTTOM") {
    return Layer::COMPONENT_BOTTOM;
  }
  else if (layerFunctionStr == "COMPONENT_TOP") {
    return Layer::COMPONENT_TOP;
  }
  else if (layerFunctionStr == "CONDFILM") {
    return Layer::CONDFILM;
  }
  else if (layerFunctionStr == "CONDFOIL") {
    return Layer::CONDFOIL;
  }
  else if (layerFunctionStr == "CONDUCTIVE_ADHESIVE") {
    return Layer::CONDUCTIVE_ADHESIVE;
  }
  else if (layerFunctionStr == "CONDUCTOR") {
    return Layer::CONDUCTOR;
  }
  else if (layerFunctionStr == "COURTYARD") {
    return Layer::COURTYARD;
  }
  else if (layerFunctionStr == "DIELADHV") {
    return Layer::DIELADHV;
  }
  else if (layerFunctionStr == "DIELBASE") {
    return Layer::DIELBASE;
  }
  else if (layerFunctionStr == "DIELCORE") {
    return Layer::DIELCORE;
  }
  else if (layerFunctionStr == "DIELPREG") {
    return Layer::DIELPREG;
  }
  else if (layerFunctionStr == "DOCUMENT") {
    return Layer::DOCUMENT;
  }
  else if (layerFunctionStr == "DRILL") {
    return Layer::DRILL;
  }
  else if (layerFunctionStr == "EMBEDDED_COMPONENT") {
    return Layer::EMBEDDED_COMPONENT;
  }
  else if (layerFunctionStr == "FIXTURE") {
    return Layer::FIXTURE;
  }
  else if (layerFunctionStr == "GLUE") {
    return Layer::GLUE;
  }
  else if (layerFunctionStr == "GRAPHIC") {
    return Layer::GRAPHIC;
  }
  else if (layerFunctionStr == "HOLEFILL") {
    return Layer::HOLEFILL;
  }
  else if (layerFunctionStr == "LANDPATTERN") {
    return Layer::LANDPATTERN;
  }
  else if (layerFunctionStr == "LEGEND") {
    return Layer::LEGEND;
  }
  else if (layerFunctionStr == "MIXED") {
    return Layer::MIXED;
  }
  else if (layerFunctionStr == "OTHER") {
    return Layer::OTHER;
  }
  else if (layerFunctionStr == "PASTEMASK") {
    return Layer::PASTEMASK;
  }
  else if (layerFunctionStr == "PLANE") {
    return Layer::PLANE;
  }
  else if (layerFunctionStr == "PROBE") {
    return Layer::PROBE;
  }
  else if (layerFunctionStr == "RESISTIVE") {
    return Layer::RESISTIVE;
  }
  else if (layerFunctionStr == "REWORK") {
    return Layer::REWORK;
  }
  else if (layerFunctionStr == "ROUTE") {
    return Layer::ROUTE;
  }
  else if (layerFunctionStr == "SIGNAL") {
    return Layer::SIGNAL;
  }
  else if (layerFunctionStr == "SILKSCREEN") {
    return Layer::SILKSCREEN;
  }
  else if (layerFunctionStr == "SOLDERBUMP") {
    return Layer::SOLDERBUMP;
  }
  else if (layerFunctionStr == "SOLDERMASK") {
    return Layer::SOLDERMASK;
  }
  else if (layerFunctionStr == "SOLDERPASTE") {
    return Layer::SOLDERPASTE;
  }
  errorInvalidAttribute("Layer", "layerFunction");
  exit(1);
}

Layer::SideType
Layer::decideSide(const QString sideStr)
{
  if (sideStr == "TOP") {
    return Layer::TOP;
  }
  else if (sideStr == "BOTTOM") {
    return Layer::BOTTOM;
  }
  else if (sideStr == "BOTH") {
    return Layer::BOTH;
  }
  else if (sideStr == "INTERNAL" || sideStr == "INNER") {
    return Layer::INTERNAL;
  }
  else if (sideStr == "ALL") {
    return Layer::ALL;
  }
  else if (sideStr == "NONE") {
    return Layer::NONE;
  }
  errorInvalidAttribute("Layer", "side");
  exit(1);
}
