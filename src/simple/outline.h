#ifndef __OUTLINE_H__
#define __OUTLINE_H__

#include "simple.h"

class Outline : public Simple
{
public:
  virtual void initialize(QXmlStreamReader& xml);
};

#endif
