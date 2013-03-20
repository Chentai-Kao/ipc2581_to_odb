#include "bomhandler.h"
#include "utils.h"

void
BomHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "Bom")) {
      return;
    }
  }
}

void
BomHandler::odbOutput(QTextStream& out, QString cmd)
{
}
