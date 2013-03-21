#include "dictionarylinedeschandler.h"

void
DictionaryLineDescHandler::run(QXmlStreamReader& xml)
{
  m_units = getUnitAttribute(xml, "DictionaryLineDesc", "units");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "EntryLineDesc")) {
      QString id = getStringAttribute(xml, "EntryLineDesc", "id");
      // id must be unique
      if (m_entryLineDescs.contains(id)) {
        qDebug("ERROR** duplicate id in DictionaryLineDesc");
        exit(1);
      }
      // create element and insert to hash table
      xml.readNextStartElement(); // <LineDesc>
      LineDesc lineDesc;
      lineDesc.initialize(xml);
      m_entryLineDescs.insert(id, lineDesc);
    }
    else if (isEndElementWithName(xml, "DictionaryLineDesc")) {
      break;
    }
  }
}
