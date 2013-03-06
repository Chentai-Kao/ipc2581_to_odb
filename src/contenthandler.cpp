#include "contenthandler.h"
#include "utils.h"

void
ContentHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "Content")) {
      return;
    }
  }
}
