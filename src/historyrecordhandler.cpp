#include "historyrecordhandler.h"
#include "utils.h"

void
HistoryRecordHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "HistoryRecord")) {
      return;
    }
  }
}

void
HistoryRecordHandler::odbOutput(QTextStream& out, QString cmd)
{
}
