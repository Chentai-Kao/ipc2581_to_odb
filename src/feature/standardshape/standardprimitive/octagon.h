#ifndef __OCTAGON_H__
#define __OCTAGON_H__

#include "standardprimitive.h"
#include "length.h"

class Octagon : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Length m_length;
};

#endif
