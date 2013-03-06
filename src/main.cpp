#include <QtCore>

#include "toplevelhandler.h"

int main()
{
  qDebug("----- Program starts -----");
  /* Open file */
  QFile *file = new QFile("test_case1.xml");
  if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("Can't open file");
    exit(1);
  }

  /* Create ODB++ file system */
  TopLevelHandler topLevelHandler;
  topLevelHandler.createOdbFileSystem();

  /* Read XML */
  QXmlStreamReader xml(file);
  topLevelHandler.run(xml);
}
