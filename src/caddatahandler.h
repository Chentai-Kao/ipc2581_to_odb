#ifndef __CADDATAHANDLER_H__
#define __CADDATAHANDLER_H__

#include <QtCore>
#include "layer.h"
#include "stackup.h"
#include "step.h"
#include "utils.h"
#include "odbfeaturefile.h"
#include "globals.h"

class CadDataHandler
{
public:
  virtual void run(QXmlStreamReader& xml, UnitsType units);
  void odbOutputMatrixAllLayers(QTextStream& out);
  void odbOutputLayerFeature(
      OdbFeatureFile& file, QString stepName, QString layerName);
  void odbOutputStepProfile(OdbFeatureFile& file, QString stepName);

  // getter
  QList<Layer>& layers() { return g_layers; }
  QList<Component>& components(QString stepName);

private:
  void odbOutputLayer(QTextStream& out, int rowNum, QString context,
      QString type, QString name, QString polarity,
      QString startName, QString endName);
  void odbOutputSingleLayer(QTextStream& out, int rowNum, Layer& layer);

  //QList<Layer> m_layers; // store in global variable 'g_layers' instead
  Stackup *m_stackup;
  QList<Step> m_steps;
};

#endif
