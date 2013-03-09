#include "dictionarylinedeschandler.h"

void
DictionaryLineDescHandler::run(QXmlStreamReader& xml)
{
  m_units = getUnitAttribute(xml, "DictionaryLineDesc", "units");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "EntryLineDesc")) {
      QString id = getAttribute(xml, "id");
      // id must be unique
      if (m_lineDescs.contains(id)) {
        qDebug("ERROR** duplicate id in DictionaryLineDesc");
        exit(1);
      }
      // create element and insert to hash table
      xml.readNextStartElement(); // <LineDesc>
      LineDesc lineDesc;
      lineDesc.initialize(xml);
      m_lineDescs.insert(id, lineDesc);
    }
    else if (isEndElementWithName(xml, "DictionaryLineDesc")) {
      break;
    }
  }
}
