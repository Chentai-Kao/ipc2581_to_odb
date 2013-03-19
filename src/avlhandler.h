#ifndef __AVLHANDLER_H__
#define __AVLHANDLER_H__

#include "handler.h"

class AvlHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml, Odb& odb);
};

#endif
