#ifndef __AVLHANDLER_H__
#define __AVLHANDLER_H__

#include <QtCore>

class AvlHandler
{
public:
  virtual void run(QXmlStreamReader& xml);
};

#endif
