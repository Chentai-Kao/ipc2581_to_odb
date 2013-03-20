#include "logisticheaderhandler.h"
#include "utils.h"

void
LogisticHeaderHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "LogisticHeader")) {
      return;
    }
  }
}

void
LogisticHeaderHandler::odbOutput(QTextStream& out, QString cmd)
{
}
