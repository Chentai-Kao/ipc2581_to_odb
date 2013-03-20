#ifndef __CADHEADERHANDLER_H__
#define __CADHEADERHANDLER_H__

#include "handler.h"
#include "utils.h"

class CadHeaderHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);
  virtual void odbOutput(QTextStream& out, QString cmd);

private:
  UnitsType m_units;
};

#endif
