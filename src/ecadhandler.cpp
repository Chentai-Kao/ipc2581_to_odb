#include "ecadhandler.h"
#include "utils.h"

void
EcadHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "Ecad")) {
      return;
    }
  }
}
