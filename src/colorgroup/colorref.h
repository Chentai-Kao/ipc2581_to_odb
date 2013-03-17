#ifndef __COLORREF_H__
#define __COLORREF_H__

#include "colorgroup.h"

class ColorRef : public ColorGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  QString m_id;
};

#endif
