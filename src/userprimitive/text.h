#ifndef __TEXT_H__
#define __TEXT_H__

#include <QtCore>
#include "utils.h"
#include "userprimitive.h"

class Text : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml) {}
};

#endif
