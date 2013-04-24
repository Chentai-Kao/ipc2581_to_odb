#include <QtCore>

#include "error.h"
#include "odb.h"
#include "toplevelhandler.h"
#include "utils.h"
#include "globals.h"

int main(int argc, char *argv[])
{
  try {
    qDebug("----- Program starts -----");

    /* parse arguments, set input/output path */
    if (argc != 3) {
      printf("Usage: ipc2581.exe src.xml dst.tgz\n"
             "Convert IPC-2581 file \'src.xml\' to ODB++ file \'dst.tgz\'\n");
      throw new MissingCmdLineArgError("");
    }

    /* Input file name */
    QString src = argv[1];
    QString dst = argv[2];

    /* Open file */
    QFile file(src);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      throw new InvalidFileError(src);
    }

    /* Read XML */
    qDebug("----- Parse XML starts -----");
    QXmlStreamReader xml(&file);
    TopLevelHandler h;
    h.run(xml);

    qDebug("----- Parse XML ends -----");
    
    /* Output to ODB file system */
    qDebug("----- ODB starts -----");
    Odb(h, dst).run();
    qDebug("----- ODB ends -----");
  } catch (Error *e) {
    e->info();
    delete e;
    exit(1);
  }
}
