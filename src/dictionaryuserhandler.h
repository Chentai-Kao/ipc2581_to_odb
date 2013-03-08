#ifndef __DICTIONARYUSERHANDLER_H__
#define __DICTIONARYUSERHANDLER_H__

#include <QtCore>
#include "handler.h"

class DictionaryUserHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
}

#endif
