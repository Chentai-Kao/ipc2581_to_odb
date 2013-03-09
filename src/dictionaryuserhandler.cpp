#include "dictionaryuserhandler.h"
#include "userprimitivefactory.h"

void
DictionaryUserHandler::run(QXmlStreamReader& xml)
{
  setUnits(getAttribute(xml, "units"));
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "EntryUser")) {
      QString id = getAttribute(xml, "id");
      xml.readNextStartElement(); // <Simple>, <Text>, <UserSpecial>
      UserPrimitive* up = UserPrimitiveFactory().create(xml);
      up->initialize(xml);
      // insert to hash table, has to be unique
      if (m_userPrimitives.contains(id)) {
        qDebug("ERROR** duplicate id in DictionaryStandard");
        exit(1);
      }
      m_userPrimitives.insert(id, up);
    }
    else if (isEndElementWithName(xml, "DictionaryUser")) {
      break;
    }
  }
}

void
DictionaryUserHandler::setUnits(const QString units)
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
    errorInvalidAttribute("DictionaryUser", "units");
    exit(1);
  }
}
