#ifndef __CADHEADERHANDLER_H__
#define __CADHEADERHANDLER_H__

#include "handler.h"
#include "utils.h"

class CadHeaderHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);

private:
  UnitsType m_units;
};

#endif
