#ifndef __BOOLEANATTRIBUTE_H__
#define __BOOLEANATTRIBUTE_H__

#include <QtCore>
#include "attribute.h"

class BooleanAttribute : public Attribute
{
public:
  virtual void initialize(QXmlStreamReader& xml);

private:
  bool m_value;
  enum BooleanAttributeName {
    critical_net,
    critical_tp,
    drc_board,
    drc_comp_height,
    drc_comp_keepin,
    drc_comp_keepout,
    drc_etch_lyrs_all,
    drc_mech,
    drc_pad_keepout,
    drc_plane_keepout,
    drc_route_keepin,
    drc_route_keepout,
    drc_tp_keepin,
    drc_tp_keepout,
    drc_trace_keepout,
    drc_via_keepout,
    full_plane,
    gold_plating,
    mount_hole,
    net_point,
    nomenclature,
    pattern_fill,
    smd,
    tear_drop,
    test_point,
    tooling_hole
  } m_name;
};

#endif
