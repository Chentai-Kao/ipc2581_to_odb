#ifndef __CADDATAHANDLER_H__
#define __CADDATAHANDLER_H__

#include <QtCore>
#include "handler.h"
#include "layer.h"
#include "stackup.h"
//#include "step.h"

class CadDataHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);

private:
  QList<Layer> m_layers;
  QList<Stackup> m_stackups;
//  QList<Step> m_steps;
};

#endif
