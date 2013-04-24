#include "odb.h"
#include "utils.h"
#include "error.h"
#include "globals.h"
#include "standardshape.h"
#include "odbfeaturefile.h"
#include "standardfont.h"
#include "steprepeat.h"

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
  createStepProfile();
  createStepHeader();
  createLayerFeature();
  createAttrlists();
  createComponents();
  createFont();
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
Odb::createStepProfile()
{
  for (int i = 0; i < m_allSteps.size(); ++i) {
    // draw the profile
    OdbFeatureFile file;
    m_handler.odbOutputStepProfile(file, m_allSteps[i]);

    // open file
    QString path = QString("steps/%1/profile").arg(m_allSteps[i].toLower());
    QFile f(m_odbRootPath + path);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&f);

    // output to file
    out << "#\n";
    out << "#Layer features\n";
    out << "#\n";
    for (int i = 0; i < file.featuresList().size(); ++i) {
      out << file.featuresList()[i];
    }
  }
}

void
Odb::createStepHeader()
{
  for (int i = 0; i < m_allSteps.size(); ++i) {
    QString path = QString("steps/%1/stephdr").arg(m_allSteps[i].toLower());
    QFile file(m_odbRootPath + path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    Step& step = m_handler.step(m_allSteps[i]);
    // datum, origin
    out << QString("X_DATUM=%1\n").arg(step.datum().x());
    out << QString("Y_DATUM=%1\n").arg(step.datum().y());
    out << QString("X_ORIGIN=%1\n").arg(0);
    out << QString("Y_ORIGIN=%1\n").arg(0);
    out << QString("\n");

    // step-repeat
    for (int i = 0; i < step.stepRepeats().size(); ++i) {
      StepRepeat& s = step.stepRepeats()[i];
      out << QString("STEP-REPEAT {\n");
      out << QString("  NAME=%1\n").arg(s.stepRef());
      out << QString("  X=%1\n").arg(s.x());
      out << QString("  Y=%1\n").arg(s.y());
      out << QString("  DX=%1\n").arg(s.dx());
      out << QString("  DY=%1\n").arg(s.dy());
      out << QString("  NX=%1\n").arg(s.nx());
      out << QString("  NY=%1\n").arg(s.ny());
      out << QString("  ANGLE=%1\n").arg(s.angle());
      out << QString("  MIRROR=%1\n").arg(s.mirror()? "YES" : "NO");
      out << QString("}\n");
      out << QString("\n");
    }

    // remaining part
    out << QString("TOP_ACTIVE=%1\n").arg(0);
    out << QString("BOTTOM_ACTIVE=%1\n").arg(0);
    out << QString("RIGHT_ACTIVE=%1\n").arg(0);
    out << QString("LEFT_ACTIVE=%1\n").arg(0);
    out << QString("ONLINE_DRC_NAME=\n");
    out << QString("ONLINE_DRC_MODE=%1\n").arg("DISABLED");
    out << QString("ONLINE_DRC_STAT=%1\n").arg("RED");
    out << QString("ONLINE_DRC_TIME=%1\n").arg(0);
    out << QString("ONLINE_DRC_BEEP_VOL=%1\n").arg(2);
    out << QString("ONLINE_DRC_BEEP_TONE=%1\n").arg(500);
    out << QString("ONLINE_NET_MODE=%1\n").arg("DISABLED");
    out << QString("ONLINE_NET_STAT=%1\n").arg("RED");
    out << QString("ONLINE_NET_TIME=%1\n").arg(0);
    out << QString("ONLINE_NET_BEEP_VOL=%1\n").arg(2);
    out << QString("ONLINE_NET_BEEP_TONE=%1\n").arg(500);
  }
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

void
Odb::createComponents()
{
  // output components in each step
  for (int i = 0; i < m_allSteps.size(); ++i) {
    /* Collect all components of this layer, then output */
    QList<Component>& components = m_handler.components(m_allSteps[i]);
    outputComponentLayer(m_allSteps[i], components, COMP_TOP);
    outputComponentLayer(m_allSteps[i], components, COMP_BOT);
  }
}

void
Odb::outputComponentLayer(
    QString stepName, QList<Component>& components, CompLayerSide side)
{
  // open file
  QString layerName = (side == COMP_TOP)? COMP_TOP_NAME : COMP_BOT_NAME;
  QFile f(m_odbRootPath + QString("steps/%1/layers/%2/components")
                                  .arg(stepName.toLower())
                                  .arg(layerName.toLower()));
  f.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&f);

  // output the component file that stores all information
  OdbComponentFile file;
  for (int i = 0; i < components.size(); ++i) {
    // output only when the component belongs to this layer (top or bot)
    QString layerRef = components[i].layerRef();
    if ((side == COMP_TOP && layerRef.contains("top", Qt::CaseInsensitive)) ||
        (side == COMP_BOT && layerRef.contains("bot", Qt::CaseInsensitive))) {
      outputComponent(file, components[i]);
    }
  }

  // output to file
  out << "#\n";
  out << "#Component attribute names\n";
  out << "#\n";
  for (int i = 0; i < file.attributeTable().size(); ++i) {
    out << QString("@%1 %2\n")
                   .arg(i)
                   .arg(file.attributeTable()[i]);
  }
  out << "#\n";
  out << "#Components\n";
  out << "#\n";
  for (int i = 0; i < file.componentList().size(); ++i) {
    out << QString("# CMP %1\n").arg(i);
    out << file.componentList()[i];
  }
  out << "\n";
}

void
Odb::outputComponent(OdbComponentFile& file, Component& components)
{
  // TODO
}

void
Odb::createFont()
{
  QFile file(m_odbRootPath + "fonts/standard");
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);

  // content predefined in "standardfont.h"
  out << standardFont;
}
