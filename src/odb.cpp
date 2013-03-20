#include "odb.h"
#include "utils.h"

void
Odb::run()
{
  createFileSystem();
  createMatrix();
  // TODO
}

void
Odb::createFileSystem()
{
  /* Delete existing ODB file system */
  deleteDir(m_odbRootPath);

  /* Create new one */
  m_dir = QDir(m_odbRootPath);
  m_dir.mkpath(".");
  m_dir.mkpath("ext");
  m_dir.mkpath("fonts");
  m_dir.mkpath("input");
  m_dir.mkpath("matrix");
  m_dir.mkpath("misc");
  m_dir.mkpath("output");
  m_dir.mkpath("stackups");
  m_dir.mkpath("steps");
  m_dir.mkpath("symbols");
  m_dir.mkpath("user");
  m_dir.mkpath("wheels");
  m_dir.mkpath("whltemps");
}

void
Odb::deleteDir(QString path)
{
  QDir dir(path);
  // delete all files in this directory
  QFileInfoList files = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
  for (int i = 0; i < files.size(); ++i) {
    dir.remove(files[i].fileName());
  }
  // recursively delete sub-directories
  QFileInfoList dirs = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
  for (int i = 0; i < dirs.size(); ++i) {
    deleteDir(dirs[i].absoluteFilePath());
  }
  // delete parent directory
  dir.rmdir(dir.absolutePath());
}

void
Odb::createMatrix()
{
  QFile file(m_odbRootPath + "matrix/matrix");
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);

  m_handler.odbOutput(out, "matrixAllSteps");
  m_handler.odbOutput(out, "matrixAllLayers");
}

void
Odb::updateOdb()
{
#if 0
  if (m_stepRefs.empty() || m_layerRefs.empty()) {
    qDebug("ERROR** steps or layers cannot be empty");
    exit(1);
  }
  if (namesStartsWithDot(m_stepRefs) || namesStartsWithDot(m_layerRefs)) {
    qDebug("ERROR** name cannot start with \'.\'");
    exit(1);
  }
  for (int i = 0; i < m_stepRefs.size(); ++i) {
    for (int j = 0; j < m_layerRefs.size(); ++j) {
      createOdbDir(QString("steps/%1/layers/%2")
                           .arg(m_stepRefs[i])
                           .arg(m_layerRefs[j]));
    }
  }
  // TODO BOM??
#endif
}

