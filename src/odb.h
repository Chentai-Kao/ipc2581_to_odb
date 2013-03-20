#ifndef __ODB_H__
#define __ODB_H__

#include <QtCore>
#include "toplevelhandler.h"
#include "settings.h"

class Odb
{
public:
  Odb(TopLevelHandler& h);
  void run();

private:
  // member functions
  void createFileSystem();
  void deleteDir(QString path); // path relative to odb root
  void createMatrix(); // Job->matrix->matrix
  void createStepLayerHierarchy();
  void createOdbDir(const QString& path); // path relative to odb root

  // data members
  TopLevelHandler m_handler;
  QDir m_dir;
  QString m_odbRootPath;
  QList<QString> m_allSteps;
  QList<QString> m_allLayers;
};

#endif
