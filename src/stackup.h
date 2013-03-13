#ifndef __STACKUP_H__
#define __STACKUP_H__

#include <QtCore>
#include "stackupgroup.h"
#include "stackupimpedance.h"

class Stackup
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  qreal m_overallThickness;
  qreal m_tolPlus;
  qreal m_tolMinus;
  enum WhereMeasuredType { LAMINATE, METAL, MASK, OTHER } m_whereMeasured;
  QList<StackupGroup> m_stackupGroups;
  QList<StackupImpedance> m_stackupImpedances;
};

#endif
