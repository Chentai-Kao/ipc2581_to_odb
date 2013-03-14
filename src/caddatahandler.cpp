#include "caddatahandler.h"

void
CadDataHandler::run(QXmlStreamReader& xml)
{
  m_stackup = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Layer") {
        Layer layer;
        layer.initialize(xml);
        m_layers.append(layer);
      }
      else if (xml.name() == "Stackup") {
        m_stackup = new Stackup();
        m_stackup->initialize(xml);
      }
      else if (xml.name() == "Step") {
        // TODO
      }
    }
    else if (isEndElementWithName(xml, "CadData")) { // </CadData>
      return;
    }
  }
}
