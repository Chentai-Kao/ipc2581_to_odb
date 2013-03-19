#include "bomhandler.h"
#include "utils.h"

void
BomHandler::run(QXmlStreamReader& xml, Odb& odb)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "Bom")) {
      return;
    }
  }
}
