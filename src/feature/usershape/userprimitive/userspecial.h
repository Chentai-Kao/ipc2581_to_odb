#ifndef __USERSPECIAL_H__
#define __USERSPECIAL_H__

#include <QtCore>
#include "utils.h"
#include "feature.h"
#include "userprimitive.h"

class UserSpecial : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  QList<Feature*> m_features;
};

#endif
