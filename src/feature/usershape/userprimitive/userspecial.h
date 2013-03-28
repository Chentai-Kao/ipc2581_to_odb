#ifndef __USERSPECIAL_H__
#define __USERSPECIAL_H__

#include <QtCore>
#include "utils.h"
#include "feature.h"
#include "userprimitive.h"

class UserSpecial : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  virtual void odbOutputLayerFeature(
      QList<QString>& symbolsTable,
      QList<QString>& attributeTable,
      QList<QString>& attributeTexts,
      QList<QString>& featuresList,
      QString polarity,
      QPointF location, Xform *xform);

private:
  QList<Feature*> m_features;
};

#endif
