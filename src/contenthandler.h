#ifndef __CONTENTHANDLER_H__
#define __CONTENTHANDLER_H__

#include "handler.h"

class ContentHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
  virtual void odbOutput(QTextStream& out, QString cmd);
  QList<QString>& allSteps() { return m_stepRefs; }
  QList<QString>& allLayers() { return m_layerRefs; }

private:
  QList<QString> m_stepRefs;
  QList<QString> m_layerRefs;
  QList<QString> m_bomRefs;
};

#endif
