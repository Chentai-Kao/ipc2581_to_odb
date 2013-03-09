#ifndef __OUTLINE_H__
#define __OUTLINE_H__

#include "userprimitive.h"
#include "polygon.h"
#include "linedesc.h"
#include "linedescgroup.h"
#include "linedescref.h"

class Outline : public UserPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  Polygon m_polygon;
  LineDescGroup* m_lineDescGroup;
};

#endif
