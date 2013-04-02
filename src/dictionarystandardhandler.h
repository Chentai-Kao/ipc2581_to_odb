#ifndef __DICTIONARYSTANDARDHANDLER_H__
#define __DICTIONARYSTANDARDHANDLER_H__

#include <QtCore>
#include "standardprimitive.h"
#include "utils.h"

class DictionaryStandardHandler
{
public:
  virtual void run(QXmlStreamReader& xml);

private:
  UnitsType m_units;
};

#endif
