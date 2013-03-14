#include "drilltool.h"
#include "utils.h"

void
DrillTool::initialize(QXmlStreamReader& xml)
{
  m_id = getStringAttribute(xml, "DrillTool", "id");
  QString type = getStringAttribute(xml, "DrillTool", "type");
  if (type == "CARBIDE") {
    m_type = DrillTool::CARBIDE;
  }
  else if (type == "ROUTER") {
    m_type = DrillTool::ROUTER;
  }
  else if (type == "LASER") {
    m_type = DrillTool::LASER;
  }
  else if (type == "FLATNOSE") {
    m_type = DrillTool::FLATNOSE;
  }
  else if (type == "EXTENSION") {
    m_type = DrillTool::EXTENSION;
  }
  else {
    errorInvalidAttribute("DrillTool", "type");
    exit(1);
  }
  m_tolPlus = getNonNegativeDoubleAttribute(xml, "DrillTool", "tolPlus");
  m_tolMinus = getNonNegativeDoubleAttribute(xml, "DrillTool", "tolMinus");
  if (hasAttribute(xml, "bitUnit")) {
    QString bitUnit = getStringAttribute(xml, "DrillTool", "bitUnit");
    if (bitUnit == "FRACTION") {
      m_bitUnit = DrillTool::FRACTION;
    }
    else if (bitUnit == "WIREGAUGE") {
      m_bitUnit = DrillTool::WIREGAUGE;
    }
    else if (bitUnit == "LETTER") {
      m_bitUnit = DrillTool::LETTER;
    }
    else if (bitUnit == "METRIC") {
      m_bitUnit = DrillTool::METRIC;
    }
    else {
      errorInvalidAttribute("DrillTool", "bitUnit");
      exit(1);
    }
  }
  m_finishSize = getNonNegativeDoubleAttribute(xml, "DrillTool", "finishSize");
  m_drillSize = getStringAttribute(xml, "DrillTool", "drillSize");
}
