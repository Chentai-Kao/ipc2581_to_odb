#include "odb.h"
#include "utils.h"
#include "settings.h"

Odb::Odb()
{
  createFileSystem();
}

void
Odb::createFileSystem()
{
  /* Delete existing ODB file system */
  deleteDir(OUTPUT_PATH);

  /* Create new one */
  m_dir = QDir(OUTPUT_PATH);
  if (!m_dir.exists()) {
    m_dir.mkpath(".");
  }
  // TODO sub-directory
}

void
Odb::deleteDir(QString path)
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
    deleteDir(dirs.at(i).absoluteFilePath());
  }
  // delete parent directory
  dir.rmdir(dir.absolutePath());
}
