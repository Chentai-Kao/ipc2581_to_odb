#ifndef __CONTENTHANDLER_H__
#define __CONTENTHANDLER_H__

#include "handler.h"

class ContentHandler : public Handler
{
public:
  void run(QString& elementText);
};

#endif
