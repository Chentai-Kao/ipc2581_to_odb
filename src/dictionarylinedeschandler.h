#ifndef __DICTIONARYLINEDESCHANDLER_H__
#define __DICTIONARYLINEDESCHANDLER_H__

#include <QtCore>
#include "handler.h"
#include "linedesc.h"
#include "utils.h"

class DictionaryLineDescHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);

private:
  UnitsType m_units;
  QHash<QString, LineDesc> m_entryLineDescs; // (id,EntryLineDesc)
};

#endif
