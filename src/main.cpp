#include <QtCore>

#include "odb.h"
#include "toplevelhandler.h"

int main()
{
  qDebug("----- Program starts -----");
  /* Open file */
  QFile *file = new QFile("test_case1.xml");
  if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("ERROR** can't open XML file");
    exit(1);
  }

  /* Read XML */
  qDebug("----- Parse XML starts -----");
  QXmlStreamReader xml(file);
  TopLevelHandler h;
  h.run(xml);

  qDebug("----- Parse XML ends -----");
  
  /* Output to ODB file system */
  qDebug("----- ODB starts -----");
  Odb(h).run();
  qDebug("----- ODB ends -----");
}
