#ifndef __CONTENTHANDLER_H__
#define __CONTENTHANDLER_H__

#include "handler.h"
#include "dictionarystandardhandler.h"
#include "dictionaryuserhandler.h"
#include "dictionarylinedeschandler.h"
#include "dictionarycolorhandler.h"

class ContentHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
  void odbOutputMatrixAllSteps(QTextStream& out);

  // getter
  QList<QString>& allSteps() { return m_stepRefs; }
  QList<QString>& allLayers() { return m_layerRefs; }

private:
  QList<QString> m_stepRefs;
  QList<QString> m_layerRefs;
  QList<QString> m_bomRefs;
  DictionaryStandardHandler *m_dictionaryStandardHandler;
  DictionaryUserHandler     *m_dictionaryUserHandler;
  DictionaryLineDescHandler *m_dictionaryLineDescHandler;
  DictionaryColorHandler    *m_dictionaryColorHandler;
};

#endif
