#ifndef __ECADHANDLER_H__
#define __ECADHANDLER_H__

#include "handler.h"
#include "cadheaderhandler.h"
#include "caddatahandler.h"

class EcadHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
  virtual void odbOutput(QTextStream& out, QString cmd);

private:
  QString m_name; // attribute "name" of <Ecad>
  CadHeaderHandler m_cadHeaderHandler;
  CadDataHandler m_cadDataHandler;
};

#endif
