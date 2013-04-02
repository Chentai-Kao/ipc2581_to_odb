#ifndef __LAYERFEATURE_H__
#define __LAYERFEATURE_H__

#include <QtCore>
#include "set.h"
#include "utils.h"

class LayerFeature
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);
  void odbOutputLayerFeature(QTextStream& out);

  // getter
  QString layerRef() { return m_layerRef; }

private:
  QString m_layerRef;
  QList<Set> m_sets;
};

#endif
