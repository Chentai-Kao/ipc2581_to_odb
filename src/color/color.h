#ifndef __COLOR_H__
#define __COLOR_H__

#include "colorgroup.h"

class Color : public ColorGroup
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  int m_r;
  int m_g;
  int m_b;
};

#endif
