#ifndef __FEATURESGROUP_H__
#define __FEATURESGROUP_H__

#include <QtCore>
#include "xform.h"
#include "feature.h"
#include "utils.h"
#include "standardprimitive.h"
#include "userprimitive.h"

class Features
{
public:
  void initialize(QXmlStreamReader& xml);
  void odbOutputLayerFeature(
      QList<QString>& symbolsTable,
      QList<QString>& attributeTable,
      QList<QString>& attributeTexts,
      QList<QString>& featuresList,
      QString polarity,
      const QHash<QString, StandardPrimitive*>& entryStandards,
      const QHash<QString, UserPrimitive*>& entryUsers);

private:
  Xform *m_xform;
  QPointF m_location;
  Feature *m_feature;
};

#endif
