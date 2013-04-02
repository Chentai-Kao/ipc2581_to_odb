#ifndef __STANDARDPRIMITIVEREF_H__
#define __STANDARDPRIMITIVEREF_H__

#include <QtCore>
#include "standardshape.h"
#include "odbfeaturefile.h"

class StandardPrimitiveRef : public StandardShape
{
public:
  virtual void initialize(QXmlStreamReader& xml, UnitsType units);
  virtual QString refId() { return m_id; }
  virtual void odbOutputLayerFeature(
      OdbFeatureFile& file,
      QString polarity,
      QPointF location, Xform *xform) {}

private:
  QString m_id;
};

#endif
