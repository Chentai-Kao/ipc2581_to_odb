#include "cadheaderhandler.h"
#include "error.h"

void
CadHeaderHandler::run(QXmlStreamReader& xml)
{
  m_units = getUnitAttribute(xml, "CadHeader", "units");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Spec") {
// TODO skipped
        //throw new NonImplementedError("CadHeader::Spec");
      }
      else if (xml.name() == "SurfaceFinish") {
// TODO skipped
        //throw new NonImplementedError("CadHeader::SurfaceFinish");
      }
      else if (xml.name() == "ChangeRec") {
// TODO skipped
        //throw new NonImplementedError("CadHeader::ChangeRec");
      }
    }
    else if (isEndElementWithName(xml, "CadHeader")) { // </CadHeader>
      return;
    }
  }
}
