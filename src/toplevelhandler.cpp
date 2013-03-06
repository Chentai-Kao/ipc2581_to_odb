#include "toplevelhandler.h"
#include "toplevelfactory.h"
#include "settings.h"
#include "utils.h"

void
TopLevelHandler::run(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    // beginning of document
    if (xml.isStartDocument()) {
      if (!checkDocumentVersionEncoding(
          xml.documentVersion(), xml.documentEncoding())) {
        break;
      }
    }
    // start element
    else if (xml.isStartElement()) {
      qDebug("%s", xml.name().toAscii().data());
      if (xml.name() == "IPC-2581") { // <IPC-2581>
        continue;
      }
      else { // <Content> <LogisticHeader> <HistoryRecord> <Bom> <Ecad> <Avl>
        TopLevelFactory topLevelFactory;
        Handler *handler = topLevelFactory.create(xml.name());
        if (handler == NULL) { // Invalid element name
          qDebug("Invalid element:%s", xml.name().toAscii().data());
          break;
        }
        // parse inner text recursively
        handler->run(xml);
        delete handler;
      }
    }
  }
}

void
TopLevelHandler::createOdbFileSystem()
{
  /* Delete existing ODB file system */
  deleteDirectory(OUTPUT_PATH);

  /* Create new one */
  QDir dir(OUTPUT_PATH);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
}

bool
TopLevelHandler::checkDocumentVersionEncoding(
    QStringRef version, QStringRef encoding)
{
  if (version != "" && version != "1.0") {
    qDebug("Invalid XML version:%s", version.toAscii().data());
    return false;
  }
  if (encoding != "" && encoding != "UTF-8" && encoding != "utf-8") {
    qDebug("Invalid XML encoding:%s", encoding.toAscii().data());
    return false;
  }
  return true;
}

void
TopLevelHandler::deleteDirectory(QString path)
{
  QDir dir(path);
  // delete all files in this directory
  QFileInfoList files = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
  for (int i = 0; i < files.size(); ++i) {
    dir.remove(files.at(i).fileName());
  }
  // recursively delete sub-directories
  QFileInfoList dirs = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
  for (int i = 0; i < dirs.size(); ++i) {
    deleteDirectory(dirs.at(i).absoluteFilePath());
  }
  // delete parent directory
  dir.rmdir(dir.absolutePath());
}
