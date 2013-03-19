#ifndef __ODB_H__
#define __ODB_H__

#include <QtCore>

class Odb
{
public:
  Odb();
  void createFileSystem();
  void deleteDir(QString path);

private:
  QDir m_dir;
};

#endif
