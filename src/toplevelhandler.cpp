#include "toplevelhandler.h"
#include "toplevelfactory.h"
#include "settings.h"
#include "utils.h"

void
TopLevelHandler::run(QXmlStreamReader& xml, Odb& odb)
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
      else { // <Content> <LogisticHeader> <HistoryRecord> <Bom> <Ecad> <Avl>
        Handler *h = TopLevelFactory().create(xml.name());
        if (h == NULL) { // Invalid element name
          qDebug("Invalid element:%s", xml.name().toAscii().data());
          break;
        }
        // parse inner text recursively
        h->run(xml, odb);
        delete h;
      }
    }
    else if (isEndElementWithName(xml, "IPC-2581")) { // </IPC-2581> the end
      return;
    }
  }
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
