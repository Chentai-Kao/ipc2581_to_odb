#ifndef __USERPRIMITIVE_H__
#define __USERPRIMITIVE_H__

#include <QtCore>
#include "utils.h"
#include "feature.h"

// Base class of "user primitive":
// Simple, Text, UserSpecial
class UserPrimitive : public Feature
{
public:
  virtual void initialize(QXmlStreamReader& xml) = 0;
};

#endif
