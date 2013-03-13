#ifndef __CADDATAHANDLER_H__
#define __CADDATAHANDLER_H__

#include "handler.h"

class CadDataHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
};

#endif
