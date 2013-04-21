#ifndef __HOLE_H__
#define __HOLE_H__

#include <QtCore>
#include "utils.h"
#include "length.h"
#include "odbfeaturefile.h"

class Hole
{
public:
  enum PlatingStatusType { PLATED, NONPLATED, VIA };
  void initialize(QXmlStreamReader& xml, UnitsType units);
  void odbOutputLayerFeature(OdbFeatureFile& file, QString polarity);

private:
  QString m_name;
  Length m_diameter;
  PlatingStatusType m_platingStatus;
  qreal m_plusTol;
  qreal m_minusTol;
  QPointF m_location; // (x,y)
};

#endif
