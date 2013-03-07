#include "utils.h"
#include "settings.h"

bool isEndElementWithName(const QXmlStreamReader& xml, const QString& name)
{
  return (xml.isEndElement() && xml.name() == name);
}

bool isStartElementWithName(const QXmlStreamReader& xml, const QString& name)
{
  return (xml.isStartElement() && xml.name() == name);
}

const QString getAttributeOrCharacters(
    QXmlStreamReader& xml, const QString attrName)
{
  QString value = getAttribute(xml, attrName);
  if (value == "") {
    value = xml.readElementText();
  }
  return value;
}

const QString getAttribute(const QXmlStreamReader& xml, const QString attrName)
{
  return xml.attributes().value("", attrName).toString();
}

void createOdbDir(const QString& path)
{
  QDir(OUTPUT_PATH).mkpath(path.toLower());
}

void errorLackAttribute(const QString elementName, const QString attributeName)
{
  qDebug("ERROR** <%s> lacks attribute \"%s\"",
      elementName.toAscii().data(),
      attributeName.toAscii().data());
}
