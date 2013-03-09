#ifndef __POLYLINE_H__
#define __POLYLINE_H__

#include "simple.h"

class Polyline : public Simple
{
public:
  virtual void initialize(QXmlStreamReader& xml);
};

#endif
