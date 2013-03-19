#include "dictionarycolorhandler.h"

void
DictionaryColorHandler::run(QXmlStreamReader& xml, Odb& odb)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (isStartElementWithName(xml, "EntryColor")) {
      QString id = getStringAttribute(xml, "EntryColor", "id");
      // id must be unique
      if (m_colors.contains(id)) {
        qDebug("ERROR** duplicate id in DictionaryColor");
        exit(1);
      }
      // create element and insert to hash table
      xml.readNextStartElement(); // <Color>
      Color color;
      color.initialize(xml);
      m_colors.insert(id, color);
    }
    else if (isEndElementWithName(xml, "DictionaryColor")) {
      break;
    }
  }
}
