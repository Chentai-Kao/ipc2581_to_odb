#ifndef __STANDARDPRIMITIVEREF_H__
#define __STANDARDPRIMITIVEREF_H__

#include <QtCore>
#include "standardshape.h"

class StandardPrimitiveRef : public StandardShape
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  QString m_id;
};

#endif
