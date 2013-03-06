#include "utils.h"

bool isEndElementWithName(const QXmlStreamReader& xml, const QString& name)
{
  return (xml.isEndElement() && xml.name() == name);
}

bool isStartElementWithName(const QXmlStreamReader& xml, const QString& name)
{
  return (xml.isStartElement() && xml.name() == name);
}
