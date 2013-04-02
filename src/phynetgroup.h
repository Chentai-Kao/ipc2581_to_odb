#ifndef __PHYNETGROUP_H__
#define __PHYNETGROUP_H__

#include <QtCore>
#include "phynet.h"
#include "utils.h"

class PhyNetGroup
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);

private:
  QString m_name;
  bool m_optimized;
  QList<PhyNet> m_phyNets;
};

#endif
