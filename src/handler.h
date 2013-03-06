#ifndef __HANDLER_H__
#define __HANDLER_H__

#include <QtCore>

class Handler
{
public:
  Handler() {};
  virtual ~Handler() {};
  virtual void run(QXmlStreamReader& xml) = 0;
};

#endif
