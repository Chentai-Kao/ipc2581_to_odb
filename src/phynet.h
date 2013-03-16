#ifndef __PHYNET_H__
#define __PHYNET_H__

#include <QtCore>
#include "phynetpoint.h"

class PhyNet
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_name;
  QList<PhyNetPoint> m_phyNetPoints;
};

#endif
