#ifndef __TOPLEVELHANDLER_H__
#define __TOPLEVELHANDLER_H__

#include <QtCore>
#include "handler.h"

class TopLevelHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
  void createOdbFileSystem();

private:
  bool checkDocumentVersionEncoding(QStringRef version, QStringRef encoding);
  void deleteDirectory(QString path);
};

#endif
