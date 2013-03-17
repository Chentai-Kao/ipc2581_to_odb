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

private:
  QList<Feature*> m_features;
};

#endif
