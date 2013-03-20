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
  virtual void odbOutput(QTextStream& out, QString cmd);

private:
  UnitsType m_units;
  QHash<QString, LineDesc> m_entryLineDescs; // (id,EntryLineDesc)
};

#endif
