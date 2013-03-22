#include "odb.h"
#include "utils.h"

Odb::Odb(TopLevelHandler& h)
{
  m_handler = h;
  m_odbRootPath = "bin/odb/";
  m_allSteps = h.allSteps();
  m_allLayers = h.allLayers();
  m_allLayers.append("COMP_+_TOP"); // because these two layers are not
  m_allLayers.append("COMP_+_BOT"); // in <LayerRef>
  m_entryStandards = m_handler.entryStandards();
  m_entryUsers = m_handler.entryUsers();
}
void
Odb::run()
{
  createFileSystem();
  createMatrix();
  createStepLayerHierarchy();
  createLayerFeature();
  // TODO
}

void
Odb::deleteOdbDir(const QString path)
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
    deleteOdbDir(dirs[i].absoluteFilePath());
  }
  // delete parent directory
  dir.rmdir(dir.absolutePath());
}

void
Odb::createOdbDir(const QString path)
{
  m_dir.mkpath(path.toLower());
}

void
Odb::createFileSystem()
{
  /* Delete existing ODB file system */
  deleteOdbDir(m_odbRootPath);

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
Odb::createMatrix()
{
  QFile file(m_odbRootPath + "matrix/matrix");
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);

  m_handler.odbOutputMatrix(out);
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
Odb::createLayerFeature()
{
  for (int i = 0; i < m_allSteps.size(); ++i) {
    for (int j = 0; j < m_allLayers.size(); ++j) {
      // open file
      QString path = QString("steps/%1/layers/%2/features")
                           .arg(m_allSteps[i])
                           .arg(m_allLayers[j])
                           .toLower();
      QFile file(m_odbRootPath + path);
      file.open(QIODevice::WriteOnly | QIODevice::Text);
      QTextStream out(&file);
      // call sub-element to draw feature
      m_handler.odbOutputLayerFeature(
          out, m_allSteps[i], m_allLayers[j], m_entryStandards, m_entryUsers);
    }
  }
}
