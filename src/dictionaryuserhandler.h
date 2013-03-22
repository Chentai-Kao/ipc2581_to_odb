#ifndef __DICTIONARYUSERHANDLER_H__
#define __DICTIONARYUSERHANDLER_H__

#include <QtCore>
#include "handler.h"
#include "userprimitive.h"

class DictionaryUserHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);

  // getter
  QHash<QString, UserPrimitive*> entryUsers() { return m_entryUsers; }

private:
  UnitsType m_units;
  QHash<QString, UserPrimitive*> m_entryUsers; // (id,EntryUser)
};

#endif
