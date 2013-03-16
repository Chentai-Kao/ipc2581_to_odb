#ifndef __OPTIONATTRIBUTE_H__
#define __OPTIONATTRIBUTE_H__

#include <QtCore>
#include "attribute.h"

class OptionAttribute : public Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  enum OptionValue {
    Area,
    Bottom,
    Buildup,
    Core,
    Gerber,
    Negative,
    Other,
    PRESSFIT,
    Positive,
    SMT,
    THMT,
    Top,
    detected,
    drilled,
    full_area,
    laser,
    non_plated,
    non_polarized,
    photo,
    pins_only,
    plated,
    polarized,
    repaired,
    via
  } m_value;
  enum OptionAttributeName { drill, comp, layer_hdi_type } m_name;
};

#endif
