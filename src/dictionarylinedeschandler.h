#ifndef __DICTIONARYLINEDESCHANDLER_H__
#define __DICTIONARYLINEDESCHANDLER_H__

#include <QtCore>
#include "linedesc.h"
#include "utils.h"

class DictionaryLineDescHandler
{
public:
  virtual void run(QXmlStreamReader& xml);
  
private:
  UnitsType m_units;
};

#endif
