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
    g_alwaysOverwrite = false;
    bool showHelpMsg = false;
    QString src, dst; // input IPC-2581 file; output path
    QCoreApplication app(argc, argv);
    QStringList args = app.arguments();
    for (int i = 1; i < args.size(); ++i) {
      if (args[i] == "-h") {
        showHelpMsg = true;
      }
      else if (args[i] == "-i" && i + 1 < args.size()) {
        src = args[i + 1];
        ++i;
      }
      else if (args[i] == "-o" && i + 1 < args.size()) {
        dst = args[i + 1];
        ++i;
      }
      else if (args[i] == "-y") {
        g_alwaysOverwrite = true;
      }
      else {
        qDebug() << "Invalid argument " << args[i].toAscii().data() << "\n";
      }
    }

    /* Show help message, or convert the IPC-2581 file. */
    if (showHelpMsg) {
      printf("Usage:\n"
             "Print this help:\n"
             "  bin/ipc2581 -h\n"
             "\n"
             "Convert IPC-2581 file \"src\" to ODB++ file \"dst\":\n"
             "  bin/ipc2581 -i src -o dst\n"
             "  (Example) bin/ipc2581 -i sample.xml -o odb\n"
             "\n"
             "If want to overwrite output path without confirmation, add -y\n"
             "  (Example) bin/ipc2581 -i sample.xml -o odb -y\n");
    }
    else {
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
    }
  } catch (Error *e) {
    e->info();
    delete e;
  }
}
