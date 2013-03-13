#ifndef __DRILLTOOL_H__
#define __DRILLTOOL_H__

#include <QtCore>

class DrillTool
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_id;
  enum DrillType { CARBIDE, ROUTER, LASER, FLATNOSE, EXTENSION } m_type;
  qreal m_toPlus;
  qreal m_toMinus;
  enum BitUnitType { FRACTION, WIREGAUGE, LETTER, METRIC } m_bitUnit;
  qreal m_finishSize;
  QString m_drillSize;
};

#endif
