#ifndef __DICTIONARYUSERHANDLER_H__
#define __DICTIONARYUSERHANDLER_H__

#include <QtCore>
#include "handler.h"
#include "userprimitive.h"

class DictionaryUserHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
  virtual void odbOutput(QTextStream& out, QString cmd);

private:
  UnitsType m_units;
  QHash<QString, UserPrimitive*> m_entryUsers; // (id,EntryUser)
};

#endif
