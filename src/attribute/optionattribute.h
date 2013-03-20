#ifndef __OPTIONATTRIBUTE_H__
#define __OPTIONATTRIBUTE_H__

#include <QtCore>
#include "attribute.h"

class OptionAttribute : public Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml);
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
  };
  enum OptionAttributeName { drill, comp, layer_hdi_type };

private:
  OptionValue m_value;
  OptionAttributeName m_name;
};

#endif
