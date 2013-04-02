#ifndef __PHYNET_H__
#define __PHYNET_H__

#include <QtCore>
#include "phynetpoint.h"
#include "utils.h"

class PhyNet
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);

private:
  QString m_name;
  QList<PhyNetPoint> m_phyNetPoints;
};

#endif
