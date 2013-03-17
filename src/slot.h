#ifndef __SLOT_H__
#define __SLOT_H__

#include <QtCore>
#include "simple.h"

class Slot
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_name;
  enum PlatingStatusType { PLATED, NONPLATED, VIA } m_platingStatus;
  qreal m_plusTol;
  qreal m_minusTol;
  QList<Simple*> m_simples; // Arc, Line, Outline, Polyline 
};

#endif
