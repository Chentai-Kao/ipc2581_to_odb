#ifndef __LAYERFEATURE_H__
#define __LAYERFEATURE_H__

#include <QtCore>
#include "set.h"

class LayerFeature
{
public:
  void initialize(QXmlStreamReader& xml);
  void odbOutputLayerFeature(QTextStream& out,
      const QHash<QString, StandardPrimitive*>& entryStandards,
      const QHash<QString, UserPrimitive*>&     entryUsers);

  // getter
  QString layerRef() { return m_layerRef; }

private:
  QString m_layerRef;
  QList<Set> m_sets;
};

#endif
