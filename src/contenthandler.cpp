#include "contenthandler.h"
#include "dictionarystandardhandler.h"
#include "dictionaryuserhandler.h"
#include "dictionarylinedeschandler.h"
#include "dictionarycolorhandler.h"
#include "utils.h"
#include "error.h"

void
ContentHandler::run(QXmlStreamReader& xml)
{
  m_dictionaryStandardHandler = NULL;
  m_dictionaryUserHandler = NULL;
  m_dictionaryLineDescHandler = NULL;
  m_dictionaryColorHandler = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "FunctionMode") {
// TODO skipped
        //throw new NonImplementedError("Content::FunctionMode");
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
// TODO skipped
        //throw new NonImplementedError("AvlRef");
      }
      else if (xml.name() == "DictionaryStandard") {
        m_dictionaryStandardHandler = new DictionaryStandardHandler();
        m_dictionaryStandardHandler->run(xml);
      }
      else if (xml.name() == "DictionaryUser") {
        m_dictionaryUserHandler = new DictionaryUserHandler();
        m_dictionaryUserHandler->run(xml);
      }
      else if (xml.name() == "DictionaryFont") {
// TODO skipped
        //throw new NonImplementedError("DictionaryFont");
      }
      else if (xml.name() == "DictionaryLineDesc") {
        m_dictionaryLineDescHandler = new DictionaryLineDescHandler();
        m_dictionaryLineDescHandler->run(xml);
      }
      else if (xml.name() == "DictionaryColor") {
        m_dictionaryColorHandler = new DictionaryColorHandler();
        m_dictionaryColorHandler->run(xml);
      }
      else if (xml.name() == "DictionaryFirmware") {
// TODO skipped
        //throw new NonImplementedError("DictionaryFirmware");
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
