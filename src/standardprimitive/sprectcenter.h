#ifndef __SPRECTCENTER_H__
#define __SPRECTCENTER_H__

#include "standardprimitive.h"

class SpRectCenter : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
private:
  qreal m_width;
  qreal m_height;
};

#endif
