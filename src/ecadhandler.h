#ifndef __ECADHANDLER_H__
#define __ECADHANDLER_H__

#include <QtCore>
#include "cadheaderhandler.h"
#include "caddatahandler.h"

class EcadHandler
{
public:
  virtual void run(QXmlStreamReader& xml);
  void odbOutputMatrixAllLayers(QTextStream& out);
  void odbOutputLayerFeature(
      QTextStream &out, QString stepName, QString layerName);

private:
  QString m_name; // attribute "name" of <Ecad>
  CadHeaderHandler m_cadHeaderHandler;
  CadDataHandler m_cadDataHandler;
};

#endif
