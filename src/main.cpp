#include <QtCore>
#include <unistd.h>

#include "error.h"
#include "odb.h"
#include "toplevelhandler.h"
#include "utils.h"

int main(int argc, char *argv[])
{
  try {
    qDebug("----- Program starts -----");

    /* parse arguments, set input/output path */
    QString src, dst; // input IPC-2581 file; output path
    int opt;
    while ((opt = getopt(argc, argv, "hi:o:")) != -1) {
      switch(opt) {
        case 'h':
          printf("Usage:\n"
                 "Print this help:\n"
                 "  bin/ipc2581 -h\n"
                 "Convert IPC-2581 file \"src\" to ODB++ file \"dst\":\n"
                 "  bin/ipc2581 -i src -o dst\n"
                 " (Example) bin/ipc2581 -i sample.xml -o odb\n");
          break;
        case 'i':
          src = optarg;
          break;
        case 'o':
          dst = optarg;
          break;
        case '?':
        default:
          throw new MissingCmdLineArgError(optopt);
          break;
      }
    }

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
  }
}
