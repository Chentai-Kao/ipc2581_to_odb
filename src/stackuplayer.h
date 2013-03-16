#ifndef __STACKUPLAYER_H__
#define __STACKUPLAYER_H__

#include <QtCore>
#include "attribute.h"

class StackupLayer
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_layerOrGroupRef;
  QString m_materialType;
  qreal m_thickness;
  qreal m_weight;
  QString m_coating;
  QString m_comment;
  QList<Attribute*> m_attributes;
};

#endif
