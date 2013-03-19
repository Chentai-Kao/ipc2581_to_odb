#include "avlhandler.h"
#include "utils.h"

void
AvlHandler::run(QXmlStreamReader& xml, Odb& odb)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "Avl")) {
      return;
    }
  }
}
