#include "cadheaderhandler.h"
#include "caddatahandler.h"
#include "ecadhandler.h"
#include "utils.h"

void
EcadHandler::run(QXmlStreamReader& xml, Odb& odb)
{
  m_name = getStringAttribute(xml, "Ecad", "name");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "CadHeader") {
        Handler *handler = new CadHeaderHandler();
        handler->run(xml, odb);
        delete handler;
      }
      else if (xml.name() == "CadData") {
        Handler *handler = new CadDataHandler();
        handler->run(xml, odb);
        delete handler;
      }
    }
    else if (isEndElementWithName(xml, "Ecad")) { // </Ecad>
      return;
    }
  }
}
