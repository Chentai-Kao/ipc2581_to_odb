#ifndef __UTILS_H__
#define __UTILS_H__

#include <QtCore>

#define print(t, s) qDebug("%s:%s", (t), (s).toAscii().data())

bool isEndElementWithName(const QXmlStreamReader& xml, const QString& name);
bool isStartElementWithName(const QXmlStreamReader& xml, const QString& name);
QString getAttributeOrCharacters(QXmlStreamReader& xml, const QString attrName);
QString getAttribute(const QXmlStreamReader& xml, const QString attrName);
void createOdbDir(const QString& path);

#endif
