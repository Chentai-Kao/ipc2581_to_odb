#ifndef __CONTENTHANDLER_H__
#define __CONTENTHANDLER_H__

#include "handler.h"

class ContentHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);

private:
  void updateOdb();
  bool namesStartsWithDot(const QList<QString>& nameList);

  QList<QString> m_stepRefs;
  QList<QString> m_layerRefs;
  QList<QString> m_bomRefs;
};

#endif
