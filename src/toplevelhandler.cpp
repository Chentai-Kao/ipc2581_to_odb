#include "toplevelhandler.h"
#include "toplevelfactory.h"
#include "utils.h"

void
TopLevelHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartDocument()) { // beginning of document
      if (!checkDocumentVersionEncoding(
          xml.documentVersion(), xml.documentEncoding())) {
        break;
      }
    }
    else if (xml.isStartElement()) { // start of element
      qDebug("%s", xml.name().toAscii().data());
      if (xml.name() == "IPC-2581") { // <IPC-2581>
        continue;
      }
      else if (xml.name() == "Content") {
        m_contentHandler.run(xml);
      }
      else if (xml.name() == "LogisticHeader") {
        m_logisticHeaderHandler.run(xml);
      }
      else if (xml.name() == "HistoryRecord") {
        m_historyRecordHandler.run(xml);
      }
      else if (xml.name() == "Bom") {
        m_bomHandler.run(xml);
      }
      else if (xml.name() == "Ecad") {
        m_ecadHandler.run(xml);
      }
      else if (xml.name() == "Avl") {
        m_avlHandler.run(xml);
      }
    }
    else if (isEndElementWithName(xml, "IPC-2581")) { // </IPC-2581> the end
      return;
    }
  }
}

void
TopLevelHandler::odbOutputMatrix(QTextStream& out)
{
  m_contentHandler.odbOutputMatrixAllSteps(out); // steps
  m_ecadHandler.odbOutputMatrixAllLayers(out); // layers
}

void
TopLevelHandler::odbOutputLayerFeature(
    QTextStream &out, QString stepName, QString layerName)
{
  m_ecadHandler.odbOutputLayerFeature(
      out, stepName, layerName,
      m_contentHandler.entryStandards(),
      m_contentHandler.entryUsers());
}

bool
TopLevelHandler::checkDocumentVersionEncoding(
    QStringRef version, QStringRef encoding)
{
  if (version != "" && version != "1.0") {
    qDebug("Invalid XML version:%s", version.toAscii().data());
    return false;
  }
  if (encoding != "" && encoding != "UTF-8" && encoding != "utf-8") {
    qDebug("Invalid XML encoding:%s", encoding.toAscii().data());
    return false;
  }
  return true;
}
