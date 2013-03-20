#include "cadheaderhandler.h"

void
CadHeaderHandler::run(QXmlStreamReader& xml)
{
  m_units = getUnitAttribute(xml, "CadHeader", "units");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Spec") {
        // TODO skipped
      }
      else if (xml.name() == "SurfaceFinish") {
        // TODO skipped
      }
      else if (xml.name() == "ChangeRec") {
        // TODO skipped
      }
    }
    else if (isEndElementWithName(xml, "CadHeader")) { // </CadHeader>
      return;
    }
  }
}

void
CadHeaderHandler::odbOutput(QTextStream& out, QString cmd)
{
}
