#include "dictionarystandardhandler.h"
#include "standardprimitivefactory.h"
#include "error.h"
#include "globals.h"

void
DictionaryStandardHandler::run(QXmlStreamReader& xml)
{
  m_units = getUnitAttribute(xml, "DictionaryStandard", "units");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "EntryStandard")) {
      QString id = getStringAttribute(xml, "EntryStandard", "id");
      // id must be unique
      if (g_entryStandards.contains(id)) {
        throw new DuplicateIdError("EntryStandard", id);
      }
      // create element and insert to hash table
      xml.readNextStartElement(); // <StandardPrimitive>
      StandardPrimitive* s = StandardPrimitiveFactory().create(xml.name());
      s->initialize(xml);
      g_entryStandards.insert(id, s);
    }
    else if (isEndElementWithName(xml, "DictionaryStandard")) {
      return;
    }
  }
}
