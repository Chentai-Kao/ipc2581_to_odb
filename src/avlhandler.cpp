#include "avlhandler.h"
#include "utils.h"

void
AvlHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isEndElementWithName(xml, "Avl")) {
      return;
    }
  }
}

void
AvlHandler::odbOutput(QTextStream& out, QString cmd)
{
}
