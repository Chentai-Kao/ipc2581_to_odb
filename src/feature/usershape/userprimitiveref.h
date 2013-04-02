#ifndef __USERPRIMITIVEREF_H__
#define __USERPRIMITIVEREF_H__

#include <QtCore>
#include "usershape.h"

class UserPrimitiveRef : public UserShape
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
