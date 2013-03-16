#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <QtCore>
#include "xform.h"

class Component
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_refDes;
  QString m_packageRef;
  QString m_part;
  QString m_layerRef;
  enum MountType { SMT, THMT, OTHER } m_mountType;
  qreal *m_weight;
  qreal *m_height;
  qreal *m_standoff;
  Xform *m_xform;
  QPointF m_location;
};

#endif
