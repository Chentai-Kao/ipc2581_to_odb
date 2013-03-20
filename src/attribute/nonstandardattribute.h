#ifndef __NONSTANDARDATTRIBUTE_H__
#define __NONSTANDARDATTRIBUTE_H__

#include <QtCore>
#include "attribute.h"

class NonstandardAttribute : public Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  enum CadPropertyType { DOUBLE, INTEGER, BOOLEAN, STRING };

private:
  QString m_name;
  QString m_value;
  CadPropertyType m_type;
};

#endif
