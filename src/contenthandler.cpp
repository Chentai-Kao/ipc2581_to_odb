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
        Handler *h = new DictionaryStandardHandler();
        h->run(xml);
        delete h;
      }
      else if (xml.name() == "DictionaryUser") {
        Handler *h = new DictionaryUserHandler();
        h->run(xml);
        delete h;
      }
      else if (xml.name() == "DictionaryFont") {
      }
      else if (xml.name() == "DictionaryLineDesc") {
        Handler *h = new DictionaryLineDescHandler();
        h->run(xml);
        delete h;
      }
      else if (xml.name() == "DictionaryColor") {
        Handler *h = new DictionaryColorHandler();
        h->run(xml);
        delete h;
      }
      else if (xml.name() == "DictionaryFirmware") {
      }
    }
    else if (isEndElementWithName(xml, "Content")) { // </Content>
      return;
    }
  }
}

void
ContentHandler::odbOutputMatrixAllSteps(QTextStream& out)
{
  for (int i = 0; i < m_stepRefs.size(); ++i) {
    out << "STEP {\n";
    out << QString("   COL=%1\n").arg(i + 1);
    out << QString("   NAME=%1\n").arg(m_stepRefs[i]);
    out << "}\n";
    out << "\n";
  }
}
