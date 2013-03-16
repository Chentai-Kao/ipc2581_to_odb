#ifndef __DOUBLEATTRIBUTE_H__
#define __DOUBLEATTRIBUTE_H__

#include <QtCore>
#include "attribute.h"

class DoubleAttribute : public Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  qreal m_value;
  enum DoubleAttributeName { pitch, board_thickness, layer_dielectric } m_name;
};

#endif
