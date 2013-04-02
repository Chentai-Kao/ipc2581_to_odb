#ifndef __OCTAGON_H__
#define __OCTAGON_H__

#include "standardprimitive.h"


class Octagon : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  qreal m_length;
};

#endif
