#ifndef __BOMHANDLER_H__
#define __BOMHANDLER_H__

#include "handler.h"

class BomHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml, Odb& odb);
};

#endif
