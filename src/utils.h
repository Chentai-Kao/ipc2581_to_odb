#ifndef __UTILS_H__
#define __UTILS_H__

#include <QtCore>

#define print(t, s) qDebug("%s:%s", (t), (s).toAscii().data())

bool isEndElementWithName(const QXmlStreamReader& xml, const QString& name);
bool isStartElementWithName(const QXmlStreamReader& xml, const QString& name);

#endif
