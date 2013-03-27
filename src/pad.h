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
  void odbOutputLayerFeature(
      QList<QString>& symbolsTable,
      QList<QString>& attributeTable,
      QList<QString>& attributeTexts,
      QList<QString>& featuresList,
      QString polarity,
      const QHash<QString, StandardPrimitive*>& entryStandards);

private:
  Xform *m_xform;
  QPointF m_location;
  StandardShape *m_standardShape;
  PinRef *m_pinRef;
};

#endif
