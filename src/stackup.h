#ifndef __STACKUP_H__
#define __STACKUP_H__

#include <QtCore>
#include "stackupgroup.h"
#include "stackupimpedance.h"
#include "utils.h"

class Stackup
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);
  enum WhereMeasuredType { LAMINATE, METAL, MASK, OTHER };

private:
  qreal m_overallThickness;
  qreal m_tolPlus;
  qreal m_tolMinus;
  WhereMeasuredType m_whereMeasured;
  QList<StackupGroup> m_stackupGroups;
  QList<StackupImpedance> m_stackupImpedances;
};

#endif
