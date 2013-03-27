#ifndef __STANDARDPRIMITIVEREF_H__
#define __STANDARDPRIMITIVEREF_H__

#include <QtCore>
#include "standardshape.h"

class StandardPrimitiveRef : public StandardShape
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  virtual QString refId() { return m_id; }
  virtual void odbOutputLayerFeature(
      QList<QString>& symbolsTable,
      QList<QString>& attributeTable,
      QList<QString>& attributeTexts,
      QList<QString>& featuresList,
      QString polarity,
      QPointF location, Xform *xform) {}

private:
  QString m_id;
};

#endif
