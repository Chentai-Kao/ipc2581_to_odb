#ifndef __HOLE_H__
#define __HOLE_H__

#include <QtCore>
#include "odbfeaturefile.h"

class Hole
{
public:
  void initialize(QXmlStreamReader& xml);
  enum PlatingStatusType { PLATED, NONPLATED, VIA };
  void odbOutputLayerFeature(OdbFeatureFile& file, QString polarity);

private:
  QString m_name;
  qreal m_diameter;
  PlatingStatusType m_platingStatus;
  qreal m_plusTol;
  qreal m_minusTol;
  QPointF m_location; // (x,y)
};

#endif
