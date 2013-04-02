#ifndef __DICTIONARYUSERHANDLER_H__
#define __DICTIONARYUSERHANDLER_H__

#include <QtCore>
#include "userprimitive.h"

class DictionaryUserHandler
{
public:
  virtual void run(QXmlStreamReader& xml);

private:
  UnitsType m_units;
};

#endif
