#include <QtCore>

#include "error.h"
#include "odb.h"
#include "toplevelhandler.h"
#include "utils.h"
#include "globals.h"

int main(int argc, char *argv[])
{
  try {
    /* parse arguments, set input/output path */
    if (argc != 2 && argc != 3) {
      printf("NAME\n"
             "  ipc2581 - convert IPC-2581 file to ODB++ format\n"
             "\n"
             "SYNOPSIS\n"
             "  ipc2581.exe input.xml [output.tgz]\n"
             "\n"
             "DESCRIPTION\n"
             "  ipc2581 converts \'input.xml\' (in IPC-2581 format)\n"
             "  to \'output.tgz\' (in ODB++ format).\n"
             "  If the output name is not specified,\n"
             "  the default is input name with extension \'.tgz\'.\n"
             "  For example, the following command\n"
             "    ipc2581.exe sample.xml\n"
             "  will generate an output \'sample.tgz\'\n"
             "\n");
      throw new MissingCmdLineArgError("");
    }

    /* Input file name */
    QString src = argv[1];
    QString jobName = QFileInfo(src).baseName();
    QString dst = (argc == 2)? jobName + ".tgz" : argv[2];

    /* Open file */
    QFile file(src);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      throw new InvalidFileError(src);
    }

    /* Read XML */
    QXmlStreamReader xml(&file);
    TopLevelHandler h;
    h.run(xml);

    /* Output to ODB file system */
    QCoreApplication app(argc, argv);
    Odb(h, dst, jobName, app.applicationDirPath()).run();
  } catch (Error *e) {
    e->info();
    delete e;
    exit(1);
  }
}
