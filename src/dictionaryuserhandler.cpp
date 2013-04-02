#include "dictionaryuserhandler.h"
#include "userprimitivefactory.h"
#include "error.h"
#include "globals.h"

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
        if (g_entryUsers.contains(id)) {
          throw new DuplicateIdError("EntryUser", id);
        }
        // create element and insert to hash table
        xml.readNextStartElement(); // <Simple>, <Text>, <UserSpecial>
        UserPrimitive* u = UserPrimitiveFactory().create(xml.name());
        u->initialize(xml, m_units);
        g_entryUsers.insert(id, u);
      }
    }
    else if (isEndElementWithName(xml, "DictionaryUser")) {
      break;
    }
  }
}
