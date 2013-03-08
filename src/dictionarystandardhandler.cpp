#include "dictionarystandardhandler.h"
#include "standardprimitivefactory.h"

void
DictionaryStandardHandler::run(QXmlStreamReader& xml)
{
  setUnits(getAttribute(xml, "units"));
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "EntryStandard")) {
      QString id = getAttribute(xml, "id");
      xml.readNextStartElement(); // <StandardPrimitive>
      StandardPrimitive* sp = StandardPrimitiveFactory().create(xml.name());
      sp->initialize(xml);
      if (m_standardPrimitives.contains(id)) {
        qDebug("ERROR** duplicate id in DictionaryStandard");
        exit(1);
      }
      m_standardPrimitives.insert(id, sp);
    }
    else if (isEndElementWithName(xml, "DictionaryStandard")) {
      return;
    }
  }
}

void
DictionaryStandardHandler::setUnits(const QString units)
{
  if (units == "MILLIMETER") {
    m_units = MILLIMETER;
  }
  else if (units == "MICRON") {
    m_units = MICRON;
  }
  else if (units == "INCH") {
    m_units = INCH;
  }
  else {
    errorInvalidAttribute("DictionaryStandard", "units");
    exit(1);
  }
}
