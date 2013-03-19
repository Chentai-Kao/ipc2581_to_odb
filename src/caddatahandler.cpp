#include "caddatahandler.h"

void
CadDataHandler::run(QXmlStreamReader& xml, Odb& odb)
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
        Step step;
        step.initialize(xml);
        m_steps.append(step);
      }
    }
    else if (isEndElementWithName(xml, "CadData")) { // </CadData>
      return;
    }
  }
}
