#ifndef __DOUBLEATTRIBUTE_H__
#define __DOUBLEATTRIBUTE_H__

#include <QtCore>
#include "attribute.h"

class DoubleAttribute : public Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  enum DoubleAttributeName { pitch, board_thickness, layer_dielectric };

private:
  qreal m_value;
  DoubleAttributeName m_name;
};

#endif
