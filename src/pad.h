#ifndef __PAD_H__
#define __PAD_H__

#include <QtCore>
#include "xform.h"
#include "standardshape.h"
#include "pinref.h"

class Pad
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  Xform *m_xform;
  QPointF m_location;
  StandardShape *m_standardShape;
  PinRef *m_pinRef;
};

#endif
