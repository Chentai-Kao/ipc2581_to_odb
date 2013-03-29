#ifndef __FEATURESGROUP_H__
#define __FEATURESGROUP_H__

#include <QtCore>
#include "xform.h"
#include "feature.h"
#include "utils.h"
#include "standardprimitive.h"
#include "userprimitive.h"
#include "odbfeaturefile.h"
#include "dictionary.h"

class Features
{
public:
  void initialize(QXmlStreamReader& xml);
  void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      const Dictionary& dictionary);

private:
  Xform *m_xform;
  QPointF m_location;
  Feature *m_feature;
};

#endif
