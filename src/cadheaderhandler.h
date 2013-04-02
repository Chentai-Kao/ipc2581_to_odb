#ifndef __CADHEADERHANDLER_H__
#define __CADHEADERHANDLER_H__

#include <QtCore>
#include "utils.h"

class CadHeaderHandler
{
public:
  virtual void run(QXmlStreamReader& xml);

  // getter
  const UnitsType units() const { return m_units; }

private:
  UnitsType m_units;
};

#endif
