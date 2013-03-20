#include "odb.h"
#include "utils.h"

Odb::Odb(TopLevelHandler& h)
{
  m_handler = h;
  m_odbRootPath = OUTPUT_PATH;
  m_allSteps = h.allSteps();
  m_allLayers = h.allLayers();
  m_allLayers.append("COMP_+_TOP");
  m_allLayers.append("COMP_+_BOT");
}
void
Odb::run()
{
  createFileSystem();
  createMatrix();
  createStepLayerHierarchy();
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
Odb::createStepLayerHierarchy()
{
  for (int i = 0; i < m_allSteps.size(); ++i) {
    for (int j = 0; j < m_allLayers.size(); ++j) {
      if (m_allSteps[i].startsWith(".") || m_allLayers[j].startsWith(".")) {
        qDebug("ERROR** name cannot start with \'.\'");
        exit(1);
      }
      createOdbDir(QString("steps/%1/layers/%2")
                           .arg(m_allSteps[i])
                           .arg(m_allLayers[j]));
    }
  }
  // TODO BOM??
}

void
Odb::createOdbDir(const QString& path)
{
  m_dir.mkpath(path.toLower());
}
