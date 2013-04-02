#ifndef __OUTLINE_H__
#define __OUTLINE_H__

#include "simple.h"
#include "polygon.h"
#include "linedesc.h"
#include "linedescgroup.h"
#include "linedescref.h"

class Outline : public Simple
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  Polygon m_polygon;
  LineDescGroup* m_lineDescGroup;
};

#endif
