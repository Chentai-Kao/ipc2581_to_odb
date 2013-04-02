#ifndef __LOGISTICHEADERHANDLER_H__
#define __LOGISTICHEADERHANDLER_H__

#include <QtCore>

class LogisticHeaderHandler
{
public:
  virtual void run(QXmlStreamReader& xml);
};

#endif
