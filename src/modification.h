#ifndef __MODIFICATION_H__
#define __MODIFICATION_H__

#include <QtCore>

class Modification
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_repairInfo;
  bool m_weldsPermitted;
};

#endif
