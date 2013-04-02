#ifndef __USERPRIMITIVE_H__
#define __USERPRIMITIVE_H__

#include <QtCore>
#include "utils.h"
#include "usershape.h"

// Base class of "user primitive":
// Simple, Text, UserSpecial
class UserPrimitive : public UserShape
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units) = 0;
  virtual QString refId() { return ""; }
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform) = 0;
};

#endif
