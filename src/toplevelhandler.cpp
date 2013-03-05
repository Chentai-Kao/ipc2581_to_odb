#include "toplevelhandler.h"
#include "toplevelfactory.h"

void
TopLevelHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    QXmlStreamReader::TokenType token = xml.readNext();
    if (token == QXmlStreamReader::StartElement) {
      qDebug("%s", xml.name().toAscii().data());
      if (xml.name() == "IPC-2581") {
        break;
        // TODO check its attributes
      }
      else {
        TopLevelFactory topLevelFactory;
        Handler *handler = topLevelFactory.create(xml.name());
        if (handler == NULL) {
          qDebug("Invalid element:%s", qPrintable(xml.name().toAscii().data()));
          break;
        }
        QString elementText = xml.readElementText(
            QXmlStreamReader::IncludeChildElements);
        handler->run(elementText);
        delete handler;
      }
    }
  }
}
