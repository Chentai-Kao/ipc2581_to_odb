#include <QtCore>

#include "toplevelhandler.h"

int main()
{
  /* Open file */
  //QFile *file = new QFile("test_case1.xml");
  QFile *file = new QFile("test_case1.xml");
  if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("Can't open file\n");
    exit(1);
  }
  qDebug("File opened!\n");

  /* Read XML */
  QXmlStreamReader xml(file);
  TopLevelHandler().run(xml);
}
