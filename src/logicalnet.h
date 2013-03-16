#ifndef __LOGICALNET_H__
#define __LOGICALNET_H__

#include <QtCore>
#include "pinref.h"

class LogicalNet
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  // data members
  QString m_name;
  enum NetClassType { CLK, FIXED, GROUND, SIGNAL, POWER, UNUSED } m_netClass;
  QList<PinRef> m_pinRefs;

  // member functions
  LogicalNet::NetClassType decideNetClassType(QXmlStreamReader& xml);
};
#endif
