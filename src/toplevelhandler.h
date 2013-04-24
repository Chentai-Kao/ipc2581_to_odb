#ifndef __TOPLEVELHANDLER_H__
#define __TOPLEVELHANDLER_H__

#include <QtCore>
#include "contenthandler.h"
#include "logisticheaderhandler.h"
#include "historyrecordhandler.h"
#include "bomhandler.h"
#include "ecadhandler.h"
#include "avlhandler.h"
#include "odbfeaturefile.h"
#include "step.h"

class TopLevelHandler
{
public:
  virtual void run(QXmlStreamReader& xml);
  void odbOutputMatrix(QTextStream& out);
  void odbOutputLayerFeature(
      OdbFeatureFile& file, QString stepName, QString layerName);
  void odbOutputStepProfile(OdbFeatureFile& file, QString stepName);

  // getter
  QList<QString>& allSteps() { return m_contentHandler.allSteps(); }
  QList<QString>& allLayers() { return m_contentHandler.allLayers(); }
  QList<Component>& components(QString stepName) {
    return m_ecadHandler.components(stepName);
  }
  Step& step(QString stepName) { return m_ecadHandler.step(stepName); }

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
