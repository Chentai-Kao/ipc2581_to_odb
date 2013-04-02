#ifndef __TARGET_H__
#define __TARGET_H__

#include <QtCore>
#include "xform.h"
#include "standardshape.h"
#include "utils.h"

class Target
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);

private:
  Xform *m_xform;
  QPointF m_location;
  StandardShape *m_standardShape;
};
#endif
