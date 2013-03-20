#ifndef __DRILLTOOL_H__
#define __DRILLTOOL_H__

#include <QtCore>

class DrillTool
{
public:
  void initialize(QXmlStreamReader& xml);
  enum DrillType { CARBIDE, ROUTER, LASER, FLATNOSE, EXTENSION };
  enum BitUnitType { FRACTION, WIREGAUGE, LETTER, METRIC };

private:
  QString m_id;
  DrillType m_type;
  qreal m_tolPlus;
  qreal m_tolMinus;
  BitUnitType m_bitUnit;
  qreal m_finishSize;
  QString m_drillSize;
};

#endif
