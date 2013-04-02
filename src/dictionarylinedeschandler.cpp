#include "dictionarylinedeschandler.h"
#include "error.h"
#include "globals.h"

void
DictionaryLineDescHandler::run(QXmlStreamReader& xml)
{
  m_units = getUnitAttribute(xml, "DictionaryLineDesc", "units");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "EntryLineDesc")) {
      QString id = getStringAttribute(xml, "EntryLineDesc", "id");
      // id must be unique
      if (g_entryLineDescs.contains(id)) {
        throw new DuplicateIdError("DictionaryLineDesc", id);
      }
      // create element and insert to hash table
      xml.readNextStartElement(); // <LineDesc>
      LineDesc l;
      l.initialize(xml);
      g_entryLineDescs.insert(id, l);
    }
    else if (isEndElementWithName(xml, "DictionaryLineDesc")) {
      break;
    }
  }
}
