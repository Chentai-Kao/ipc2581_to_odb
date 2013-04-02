#ifndef __HISTORYRECORDHANDLER_H__
#define __HISTORYRECORDHANDLER_H__

#include <QtCore>

class HistoryRecordHandler
{
public:
  virtual void run(QXmlStreamReader& xml);
};

#endif
