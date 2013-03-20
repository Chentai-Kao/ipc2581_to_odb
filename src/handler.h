#ifndef __HANDLER_H__
#define __HANDLER_H__

#include <QtCore>

class Handler
{
public:
  Handler() {};
  virtual ~Handler() {};
  virtual void run(QXmlStreamReader& xml) = 0;
  virtual void odbOutput(QTextStream& out, QString cmd) = 0;
};

#endif
