#ifndef __OVAL_H__
#define __OVAL_H__

#include "standardprimitive.h"
#include "length.h"

class Oval : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file, QString polarity,
      QPointF location, Xform *xform);

private:
  Length m_width;
  Length m_height;
};

#endif
