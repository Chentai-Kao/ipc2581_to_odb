#ifndef __TEXTATTRIBUTE_H__
#define __TEXTATTRIBUTE_H__

#include <QtCore>
#include "attribute.h"

class TextAttribute : public Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  enum TextAttributeName {
    bit,
    geometry,
    area_name,
    customer,
    comment,
    technology,
    eda_layers
  };

private:
  QString m_value;
  TextAttributeName m_name;
};

#endif
