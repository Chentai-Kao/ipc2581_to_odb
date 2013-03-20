#ifndef __ODB_H__
#define __ODB_H__

#include <QtCore>
#include "toplevelhandler.h"
#include "settings.h"

class Odb
{
public:
  Odb(TopLevelHandler& h) : m_handler(h), m_odbRootPath(OUTPUT_PATH) {};
  void run();

private:
  // member functions
  void createFileSystem();
  void deleteDir(QString path); // path relative to odb root
  void createMatrix(); // Job->matrix->matrix
  void updateOdb(); // TODO not used yet

  // data members
  TopLevelHandler m_handler;
  QDir m_dir;
  QString m_odbRootPath;
};

#endif
