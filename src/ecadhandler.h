#ifndef __ECADHANDLER_H__
#define __ECADHANDLER_H__

#include <QtCore>
#include "cadheaderhandler.h"
#include "caddatahandler.h"
#include "odbfeaturefile.h"
#include "step.h"

class EcadHandler
{
public:
  virtual void run(QXmlStreamReader& xml);
  void odbOutputMatrixAllLayers(QTextStream& out);
  void odbOutputLayerFeature(
      OdbFeatureFile& file, QString stepName, QString layerName);
  void odbOutputStepProfile(OdbFeatureFile& file, QString stepName);

  // getter
  QList<Component>& components(QString stepName) {
    return m_cadDataHandler.components(stepName);
  }
  Step& step(QString stepName) { return m_cadDataHandler.step(stepName); }

private:
  QString m_name; // attribute "name" of <Ecad>
  CadHeaderHandler m_cadHeaderHandler;
  CadDataHandler m_cadDataHandler;
};

#endif
