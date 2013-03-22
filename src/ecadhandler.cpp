#include "ecadhandler.h"
#include "utils.h"

void
EcadHandler::run(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "Ecad", "name");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "CadHeader") {
        m_cadHeaderHandler.run(xml);
      }
      else if (xml.name() == "CadData") {
        m_cadDataHandler.run(xml);
      }
    }
    else if (isEndElementWithName(xml, "Ecad")) { // </Ecad>
      return;
    }
  }
}

void
EcadHandler::odbOutputMatrixAllLayers(QTextStream& out)
{
  m_cadDataHandler.odbOutputMatrixAllLayers(out);
}

void
EcadHandler::odbOutputLayerFeature(
    QTextStream &out, QString stepName, QString layerName)
{
  m_cadDataHandler.odbOutputLayerFeature(out, stepName, layerName);
}
