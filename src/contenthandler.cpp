#include "contenthandler.h"
#include "settings.h"
#include "utils.h"

void
ContentHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "Content")) {
      return;
    }
    if (xml.isStartElement()) {
      if (xml.name() == "FunctionMode") {
      }
      else if (xml.name() == "StepRef") {
        QString stepName = getAttributeOrCharacters(xml, "name");
        m_steps.append(stepName);
      }
      else if (xml.name() == "LayerRef") {
        QString layerName = getAttributeOrCharacters(xml, "name");
        m_layers.append(layerName);
      }
      else if (xml.name() == "BomRef") {
        QString bomName = getAttributeOrCharacters(xml, "name");
        m_boms.append(bomName);
      }
      else if (xml.name() == "AvlRef") {
      }
      else if (xml.name() == "DictionaryStandard") {
      }
      else if (xml.name() == "DictionaryUser") {
      }
      else if (xml.name() == "DictionaryFont") {
      }
      else if (xml.name() == "DictionaryLineDesc") {
      }
      else if (xml.name() == "DictionaryColor") {
      }
      else if (xml.name() == "DictionaryFirmware") {
      }
    }
  }
}
