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
  QXmlStreamReader xml(file);
  Odb odb;
  TopLevelHandler().run(xml, odb);
}
