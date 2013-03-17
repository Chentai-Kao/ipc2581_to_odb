#include "dictionaryuserhandler.h"
#include "userprimitivefactory.h"

void
DictionaryUserHandler::run(QXmlStreamReader& xml)
{
  m_units = getUnitAttribute(xml, "DictionaryUser", "units");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "EntryUser") {
        QString id = getStringAttribute(xml, "EntryUser", "id");
        // id must be unique
        if (m_entryUsers.contains(id)) {
          qDebug("ERROR** duplicate id in DictionaryUser");
          exit(1);
        }
        // create element and insert to hash table
        xml.readNextStartElement(); // <Simple>, <Text>, <UserSpecial>
        UserPrimitive* u = UserPrimitiveFactory().create(xml.name());
        u->initialize(xml);
        m_entryUsers.insert(id, u);
      }
    }
    else if (isEndElementWithName(xml, "DictionaryUser")) {
      break;
    }
  }
}
