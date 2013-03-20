#ifndef __DICTIONARYSTANDARDHANDLER_H__
#define __DICTIONARYSTANDARDHANDLER_H__

#include <QtCore>
#include "handler.h"
#include "standardprimitive.h"
#include "utils.h"

class DictionaryStandardHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
  virtual void odbOutput(QTextStream& out, QString cmd);

private:
  UnitsType m_units;
  QHash<QString, StandardPrimitive*> m_entryStandards; // (id,EntryStandard)
};

#endif
