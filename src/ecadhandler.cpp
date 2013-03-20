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
EcadHandler::odbOutput(QTextStream& out, QString cmd)
{
  if (cmd == "matrixAllLayers") {
    m_cadDataHandler.odbOutput(out, cmd);
  }
}
