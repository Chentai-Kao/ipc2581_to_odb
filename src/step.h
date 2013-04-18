#ifndef __STEP_H__
#define __STEP_H__

#include <QtCore>
#include "contour.h"
#include "package.h"
#include "component.h"
#include "logicalnet.h"
#include "phynetgroup.h"
#include "layerfeature.h"
#include "attribute.h"
#include "utils.h"
#include "odbfeaturefile.h"

class Step
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);

  // getter
  QString name() { return m_name; }
  void odbOutputLayerFeature(OdbFeatureFile& file, const QString layerName);

private:
  QString m_name;
  QList<Attribute*> m_attributes;
  QPointF m_datum; // (x,y)
  Contour m_profile;
  QList<Package> m_packages;
  //QList<Component> m_components; // store in global variable 'g_components'
  QList<LogicalNet> m_logicalNets;
  QList<PhyNetGroup> m_phyNetGroups;
  QList<LayerFeature> m_layerFeatures;
};

#endif
