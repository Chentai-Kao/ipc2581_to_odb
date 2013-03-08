#ifndef __RECTCENTER_H__
#define __RECTCENTER_H__

#include "standardprimitive.h"

class RectCenter : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_width;
  qreal m_height;
};

#endif
