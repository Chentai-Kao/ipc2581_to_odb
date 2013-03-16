#ifndef __LAYERFEATURE_H__
#define __LAYERFEATURE_H__

#include <QtCore>
#include "set.h"

class LayerFeature
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_layerRef;
  QList<Set> m_sets;
};

#endif
