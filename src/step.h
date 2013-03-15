#ifndef __STEP_H__
#define __STEP_H__

#include <QtCore>
#include "contour.h"
#include "package.h"
//#include "component.h"
//#include "logicalnet.h"
//#include "phynetgroup.h"
//#include "layerfeature.h"

class Step
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_name;
  QPointF m_datum; // (x,y)
  Contour m_profile;
  QList<Package> m_packages;
//  QList<Component> m_components;
//  QList<LogicalNet> m_logicalNets;
//  QList<PhyNetGroup> m_phyNetGroups;
//  QList<LayerFeature> m_layerFeatures;
};

#endif
