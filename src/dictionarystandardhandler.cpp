#include "dictionarystandardhandler.h"
#include "standardprimitivefactory.h"

void
DictionaryStandardHandler::run(QXmlStreamReader& xml)
{
  m_units = getUnitAttribute(xml, "DictionaryUser", "units");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "EntryStandard")) {
      QString id = getAttribute(xml, "id");
      // id must be unique
      if (m_standardPrimitives.contains(id)) {
        qDebug("ERROR** duplicate id in DictionaryStandard");
        exit(1);
      }
      // create element and insert to hash table
      xml.readNextStartElement(); // <StandardPrimitive>
      StandardPrimitive* sp = StandardPrimitiveFactory().create(xml);
      sp->initialize(xml);
      m_standardPrimitives.insert(id, sp);
    }
    else if (isEndElementWithName(xml, "DictionaryStandard")) {
      return;
    }
  }
}
