#ifndef __PAD_H__
#define __PAD_H__

#include <QtCore>
#include "xform.h"
#include "standardshape.h"
#include "pinref.h"
#include "utils.h"
#include "standardprimitive.h"

class Pad
{
public:
  void initialize(QXmlStreamReader& xml);
  OdbFeatureRecord createFeatureRecord(
      const QHash<QString, StandardPrimitive*>& entryStandards);

private:
  Xform *m_xform;
  QPointF m_location;
  StandardShape *m_standardShape;
  PinRef *m_pinRef;
};

#endif
