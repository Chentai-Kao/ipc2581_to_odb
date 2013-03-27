#include <QtCore>

#include "error.h"
#include "odb.h"
#include "toplevelhandler.h"
#include "utils.h"

int main()
{
  try {
    qDebug("----- Program starts -----");
    /* Open file */
    QString fileName = "test_case1.xml";
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
      throw new InvalidFileError(fileName);
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
  } catch (Error *e) {
    e->info();
    delete e;
  }
}
