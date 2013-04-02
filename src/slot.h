#ifndef __SLOT_H__
#define __SLOT_H__

#include <QtCore>
#include "simple.h"
#include "utils.h"

class Slot
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);
  enum PlatingStatusType { PLATED, NONPLATED, VIA };

private:
  QString m_name;
  PlatingStatusType m_platingStatus;
  qreal m_plusTol;
  qreal m_minusTol;
  QList<Simple*> m_simples; // Arc, Line, Outline, Polyline 
};

#endif
