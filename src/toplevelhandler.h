#ifndef __TOPLEVELHANDLER_H__
#define __TOPLEVELHANDLER_H__

#include <QtCore>
#include "handler.h"
#include "contenthandler.h"
#include "logisticheaderhandler.h"
#include "historyrecordhandler.h"
#include "bomhandler.h"
#include "ecadhandler.h"
#include "avlhandler.h"

class TopLevelHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
  void odbOutputMatrix(QTextStream& out);
  void odbOutputLayerFeature(
      QTextStream &out, QString stepName, QString layerName,
      const QHash<QString, StandardPrimitive*>& entryStandards,
      const QHash<QString, UserPrimitive*>&     entryUsers);

  // getter
  QList<QString>& allSteps() { return m_contentHandler.allSteps(); }
  QList<QString>& allLayers() { return m_contentHandler.allLayers(); }
  QHash<QString, StandardPrimitive*> entryStandards() {
    return m_contentHandler.entryStandards();
  }
  QHash<QString, UserPrimitive*> entryUsers() {
    return m_contentHandler.entryUsers();
  }

private:
  // member functions
  bool checkDocumentVersionEncoding(QStringRef version, QStringRef encoding);

  // data member
  ContentHandler        m_contentHandler;
  LogisticHeaderHandler m_logisticHeaderHandler;
  HistoryRecordHandler  m_historyRecordHandler;
  BomHandler            m_bomHandler;
  EcadHandler           m_ecadHandler;
  AvlHandler            m_avlHandler;
};

#endif
