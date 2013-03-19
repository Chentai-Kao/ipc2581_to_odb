#ifndef __HANDLER_H__
#define __HANDLER_H__

#include <QtCore>
#include "odb.h"

class Handler
{
public:
  Handler() {};
  virtual ~Handler() {};
  virtual void run(QXmlStreamReader& xml, Odb& odb) = 0;
};

#endif
