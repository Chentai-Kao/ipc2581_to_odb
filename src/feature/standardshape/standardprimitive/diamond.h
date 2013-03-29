#ifndef __DIAMOND_H__
#define __DIAMOND_H__

#include "standardprimitive.h"


class Diamond : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform);

private:
  qreal m_width;
  qreal m_height;
};

#endif
