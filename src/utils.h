#ifndef __UTILS_H__
#define __UTILS_H__

#include <QtCore>

#define print(t, s) qDebug("%s:%s", (t), (s).toAscii().data())

enum UnitsType {
  MILLIMETER,
  MICRON,
  INCH
};

bool isEndElementWithName(const QXmlStreamReader& xml, const QString& name);
bool isStartElementWithName(const QXmlStreamReader& xml, const QString& name);
const QString getAttributeOrCharacters(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
bool hasAttribute(const QXmlStreamReader& xml, const QString attrName);
const QString getAttribute(const QXmlStreamReader& xml, const QString attrName);
void createOdbDir(const QString& path);
void errorInvalidAttribute(
    const QString elementName, const QString attributeName);
qreal getNonNegativeDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
qreal getDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
int getNonNegativeIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
int getIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
bool getBoolAttribute(QXmlStreamReader& xml, const QString attributeName);
UnitsType getUnitAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
QString getStringAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);

#endif
