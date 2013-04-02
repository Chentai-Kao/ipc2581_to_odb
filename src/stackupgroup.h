#ifndef __STACKUPGROUP_H__
#define __STACKUPGROUP_H__

#include <QtCore>
#include "stackuplayer.h"
#include "utils.h"

class StackupGroup
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);

private:
  QString m_name;
  qreal m_thickness;
  qreal m_tolPlus;
  qreal m_tolMinus;
  QList<StackupLayer> m_stackupLayers;
};

#endif
