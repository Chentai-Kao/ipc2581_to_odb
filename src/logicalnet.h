#ifndef __LOGICALNET_H__
#define __LOGICALNET_H__

#include <QtCore>
#include "pinref.h"

class LogicalNet
{
public:
  void initialize(QXmlStreamReader& xml);
  enum NetClassType { CLK, FIXED, GROUND, SIGNAL, POWER, UNUSED };

private:
  // member functions
  NetClassType decideNetClassType(QXmlStreamReader& xml);

  // data members
  QString m_name;
  NetClassType m_netClass;
  QList<PinRef> m_pinRefs;
};
#endif
