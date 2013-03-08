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

void errorInvalidAttribute(
    const QString elementName, const QString attributeName)
{
  qDebug("ERROR** invalid attribute \"%s\" in <%s>",
      attributeName.toAscii().data(),
      elementName.toAscii().data());
}

qreal getNonNegativeDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  qreal value = getDoubleAttribute(xml, elementName, attributeName);
  if (value < 0) {
    errorInvalidAttribute(elementName, attributeName);
    exit(1);
  }
  return value;
}

qreal getDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  bool ok;
  qreal value = getAttribute(xml, attributeName).toDouble(&ok);
  if (!ok) {
    errorInvalidAttribute(elementName, attributeName);
    exit(1);
  }
  return value;
}

int getNonNegativeIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  int value = getIntAttribute(xml, elementName, attributeName);
  if (value < 0) {
    errorInvalidAttribute(elementName, attributeName);
    exit(1);
  }
  return value;
}

int getIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  bool ok;
  int value = getAttribute(xml, attributeName).toInt(&ok);
  if (!ok) {
    errorInvalidAttribute(elementName, attributeName);
    exit(1);
  }
  return value;
}

bool getBoolAttribute(QXmlStreamReader& xml, const QString attributeName)
{
  return (getAttribute(xml, attributeName) == "TRUE");
}
