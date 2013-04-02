#ifndef __FEATURESGROUP_H__
#define __FEATURESGROUP_H__

#include <QtCore>
#include "xform.h"
#include "feature.h"
#include "utils.h"
#include "standardprimitive.h"
#include "userprimitive.h"
#include "odbfeaturefile.h"

class Features
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);
  void odbOutputLayerFeature(OdbFeatureFile& file, QString polarity);

private:
  Xform *m_xform;
  QPointF m_location;
  Feature *m_feature;
};

#endif
