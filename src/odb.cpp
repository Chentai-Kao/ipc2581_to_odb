#include "odb.h"
#include "utils.h"
#include "error.h"
#include "globals.h"
#include "standardshape.h"

Odb::Odb(TopLevelHandler& h, QString& dst)
{
  m_handler = h;

  // handle the output path
  if (QFile(dst).exists() && !g_alwaysOverwrite) {
    printf("Output path exists. Do you want to overwrite? [Y/n] ");
    char c = getc(stdin);
    if (c == 'N' || c == 'n') {
      printf("Canceled by user.\n");
      exit(0);
    }
  }
  if (!dst.endsWith("/")) { // make sure the path ends with '/'
    dst.append("/");
  }
  m_odbRootPath = dst;

  m_allSteps = m_handler.allSteps();
  m_allLayers = m_handler.allLayers();
  m_allLayers.append(COMP_BOT_NAME); // comp_+_bot
  m_allLayers.append(COMP_TOP_NAME); // comp_+_top
}

void
Odb::run()
{
  createFileSystem();
  createMatrix();
  createStepLayerDirs();
  createLayerFeature();
  createAttrlists();
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
Odb::createStepLayerDirs()
{
  for (int i = 0; i < m_allSteps.size(); ++i) {
    if (m_allSteps[i].startsWith(".")) {
      throw new NameStartWithDotError(m_allSteps[i]);
    }
    for (int j = 0; j < m_allLayers.size(); ++j) {
      if (m_allLayers[j].startsWith(".")) {
        throw new NameStartWithDotError(m_allLayers[j]);
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
    /* Collect all features to be output in g_layerFeatureFiles
     * Each feature file has 4 sections:
     * Symbols table, Attribute table, Attribute texts, and Features list.
     * Collect the full information of them, then output to file.
     */
    g_layerFeatureFiles.clear();
    for (int j = 0; j < m_allLayers.size(); ++j) {
      g_layerFeatureFiles.insert(m_allLayers[j], OdbFeatureFile());
    }

    /* Collect features, save in corresponding feature file */
    for (int j = 0; j < m_allLayers.size(); ++j) {
      m_handler.odbOutputLayerFeature(
          g_layerFeatureFiles[m_allLayers[j]],
          m_allSteps[i],
          m_allLayers[j]);
    }

    /* Actually output features to file */
    for (int j = 0; j < m_allLayers.size(); ++j) {
      // for "comp_+_bot" and "comp_+_top", there is no feature file
      if (m_allLayers[j] != COMP_BOT_NAME &&
          m_allLayers[j] != COMP_TOP_NAME) {
        // open file
        QString path = QString("steps/%1/layers/%2/features")
                               .arg(m_allSteps[i].toLower())
                               .arg(m_allLayers[j].toLower());
        QFile f(m_odbRootPath + path);
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&f);

        // find the feature file that stores this layer's feature
        OdbFeatureFile& file = g_layerFeatureFiles[m_allLayers[j]];

        // output to file
        out << "#\n";
        out << "#Feature symbol names\n";
        out << "#\n";
        for (int i = 0; i < file.symbolsTable().size(); ++i) {
          out << QString("$%1 %2\n")
                         .arg(i)
                         .arg(file.symbolsTable()[i]);
        }
        out << "#\n";
        out << "#Feature attribute names\n";
        out << "#\n";
        for (int i = 0; i < file.attributeTable().size(); ++i) {
          out << file.attributeTable()[i];
        }
        out << "#\n";
        out << "#Feature attribute text strings\n";
        out << "#\n";
        for (int i = 0; i < file.attributeTexts().size(); ++i) {
          out << file.attributeTexts()[i];
        }
        out << "#\n";
        out << "#Layer features\n";
        out << "#\n";
        for (int i = 0; i < file.featuresList().size(); ++i) {
          out << file.featuresList()[i];
        }
      }
    }
  }
}

void
Odb::createAttrlists()
{
  createJobAttribute();
  for (int i = 0; i < m_allSteps.size(); ++i) {
    createStepAttribute(m_allSteps[i]);
    for (int j = 0; j < m_allLayers.size(); ++j) {
      createLayerAttribute(m_allSteps[i], m_allLayers[j]);
    }
  }
}

void
Odb::createJobAttribute()
{
  QFile file(m_odbRootPath + "misc/attrlist");
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);

  // TODO (empty attrlist)
}

void
Odb::createStepAttribute(QString stepName)
{
  QFile file(m_odbRootPath + QString("steps/%1/attrlist")
                                     .arg(stepName.toLower()));
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);

  // TODO (empty attrlist)
}

void
Odb::createLayerAttribute(QString stepName, QString layerName)
{
  QFile file(m_odbRootPath + QString("steps/%1/layers/%2/attrlist")
                                     .arg(stepName.toLower())
                                     .arg(layerName.toLower()));
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);

  // TODO (empty attrlist)
}
