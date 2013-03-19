#include "historyrecordhandler.h"
#include "utils.h"

void
HistoryRecordHandler::run(QXmlStreamReader& xml, Odb& odb)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "HistoryRecord")) {
      return;
    }
  }
}
