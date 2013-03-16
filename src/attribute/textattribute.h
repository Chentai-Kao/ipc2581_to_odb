#ifndef __TEXTATTRIBUTE_H__
#define __TEXTATTRIBUTE_H__

#include <QtCore>
#include "attribute.h"

class TextAttribute : public Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  QString m_value;
  enum TextAttributeName {
    bit,
    geometry,
    area_name,
    customer,
    comment,
    technology,
    eda_layers
  } m_name;
};

#endif
