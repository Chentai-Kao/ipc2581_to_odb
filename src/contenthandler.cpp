#include "contenthandler.h"
#include "settings.h"
#include "dictionarystandardhandler.h"
#include "dictionaryuserhandler.h"
#include "dictionarylinedeschandler.h"
#include "dictionarycolorhandler.h"
#include "utils.h"

void
ContentHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "FunctionMode") {
      }
      else if (xml.name() == "StepRef") {
        QString stepRefName = getAttributeOrCharacters(xml, "StepRef", "name");
        m_stepRefs.append(stepRefName);
      }
      else if (xml.name() == "LayerRef") {
        QString layerRefName = getAttributeOrCharacters(xml, "StepRef", "name");
        m_layerRefs.append(layerRefName);
      }
      else if (xml.name() == "BomRef") {
        QString bomRefName = getAttributeOrCharacters(xml, "StepRef", "name");
        m_bomRefs.append(bomRefName);
      }
      else if (xml.name() == "AvlRef") {
      }
      else if (xml.name() == "DictionaryStandard") {
        Handler *handler = new DictionaryStandardHandler();
        handler->run(xml);
        delete handler;
      }
      else if (xml.name() == "DictionaryUser") {
        Handler *handler = new DictionaryUserHandler();
        handler->run(xml);
        delete handler;
      }
      else if (xml.name() == "DictionaryFont") {
      }
      else if (xml.name() == "DictionaryLineDesc") {
        Handler *handler = new DictionaryLineDescHandler();
        handler->run(xml);
        delete handler;
      }
      else if (xml.name() == "DictionaryColor") {
        Handler *handler = new DictionaryColorHandler();
        handler->run(xml);
        delete handler;
      }
      else if (xml.name() == "DictionaryFirmware") {
      }
    }
    else if (isEndElementWithName(xml, "Content")) {
      updateOdb();
      return;
    }
  }
}

void
ContentHandler::updateOdb()
{
  if (m_stepRefs.empty() || m_layerRefs.empty()) {
    qDebug("ERROR** steps or layers cannot be empty");
    exit(1);
  }
  if (namesStartsWithDot(m_stepRefs) || namesStartsWithDot(m_layerRefs)) {
    qDebug("ERROR** name cannot start with \'.\'");
    exit(1);
  }
  for (int i = 0; i < m_stepRefs.size(); ++i) {
    for (int j = 0; j < m_layerRefs.size(); ++j) {
      createOdbDir(QString("steps/") + m_stepRefs.at(i) + "/" + m_layerRefs.at(j));
    }
  }
  // TODO BOM??
}

bool
ContentHandler::namesStartsWithDot(const QList<QString>& nameList)
{
  for (int i = 0; i < nameList.size(); ++i) {
    if (nameList.at(i).startsWith(".")) {
      return true;
    }
  }
  return false;
}
