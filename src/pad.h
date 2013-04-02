#ifndef __PAD_H__
#define __PAD_H__

#include <QtCore>
#include "xform.h"
#include "standardshape.h"
#include "pinref.h"
#include "utils.h"
#include "standardprimitive.h"
#include "odbfeaturefile.h"

class Pad
{
public:
  void initialize(QXmlStreamReader& xml);
  void odbOutputLayerFeature(OdbFeatureFile& file, QString polarity);

private:
  Xform *m_xform;
  QPointF m_location;
  StandardShape *m_standardShape;
  PinRef *m_pinRef;
};

#endif
