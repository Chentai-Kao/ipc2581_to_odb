#ifndef __BOMHANDLER_H__
#define __BOMHANDLER_H__

#include <QtCore>

class BomHandler
{
public:
  virtual void run(QXmlStreamReader& xml);
};

#endif
