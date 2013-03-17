#ifndef __USERPRIMITIVEREF_H__
#define __USERPRIMITIVEREF_H__

#include <QtCore>
#include "usershape.h"

class UserPrimitiveRef : public UserShape
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  QString m_id;
};

#endif
