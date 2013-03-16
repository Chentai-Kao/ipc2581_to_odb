#ifndef __PHYNETPOINT_H__
#define __PHYNETPOINT_H__

#include <QtCore>
#include "standardshape.h"

class PhyNetPoint
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QPointF m_point; // (x,y)
  QString m_layerRef;
  enum NetPointType { END, MIDDLE } m_netNode;
  enum ExposureType {
    EXPOSED,
    COVERED_PRIMARY,
    COVERED_SECONDARY,
    COVERED
  } m_exposure;
  QString *m_layerIndex;
  QString *m_comment;
  bool *m_via;
  bool *m_fiducial;
  bool *m_test;
  qreal *m_staggerX;
  qreal *m_staggerY;
  qreal *m_staggerRadius;
  StandardShape *m_standardShape;
};

#endif
