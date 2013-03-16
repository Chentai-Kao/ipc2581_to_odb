#ifndef __INTEGERATTRIBUTE_H__
#define __INTEGERATTRIBUTE_H__

#include <QtCore>
#include "attribute.h"

class IntegerAttribute : public Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  int m_value;
  enum IntegerAttributeName {
    cut_line,
    design_origin_x,
    design_origin_y,
    num_local_fiducials,
    pilot_hole,
    testpoint_count
  } m_name;
};

#endif
