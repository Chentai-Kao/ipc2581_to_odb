#include "booleanattribute.h"
#include "utils.h"

void
BooleanAttribute::initialize(QXmlStreamReader& xml)
{
  m_value = getBoolAttribute(xml, "value");
  QString name = getStringAttribute(xml, "BooleanAttribute", "name");
  if (name == "critical_net") {
    m_name = BooleanAttribute::critical_net;
  }
  else if (name == "critical_tp") {
    m_name = BooleanAttribute::critical_tp;
  }
  else if (name == "drc_board") {
    m_name = BooleanAttribute::drc_board;
  }
  else if (name == "drc_comp_height") {
    m_name = BooleanAttribute::drc_comp_height;
  }
  else if (name == "drc_comp_keepin") {
    m_name = BooleanAttribute::drc_comp_keepin;
  }
  else if (name == "drc_comp_keepout") {
    m_name = BooleanAttribute::drc_comp_keepout;
  }
  else if (name == "drc_etch_lyrs_all") {
    m_name = BooleanAttribute::drc_etch_lyrs_all;
  }
  else if (name == "drc_mech") {
    m_name = BooleanAttribute::drc_mech;
  }
  else if (name == "drc_pad_keepout") {
    m_name = BooleanAttribute::drc_pad_keepout;
  }
  else if (name == "drc_plane_keepout") {
    m_name = BooleanAttribute::drc_plane_keepout;
  }
  else if (name == "drc_route_keepin") {
    m_name = BooleanAttribute::drc_route_keepin;
  }
  else if (name == "drc_route_keepout") {
    m_name = BooleanAttribute::drc_route_keepout;
  }
  else if (name == "drc_tp_keepin") {
    m_name = BooleanAttribute::drc_tp_keepin;
  }
  else if (name == "drc_tp_keepout") {
    m_name = BooleanAttribute::drc_tp_keepout;
  }
  else if (name == "drc_trace_keepout") {
    m_name = BooleanAttribute::drc_trace_keepout;
  }
  else if (name == "drc_via_keepout") {
    m_name = BooleanAttribute::drc_via_keepout;
  }
  else if (name == "full_plane") {
    m_name = BooleanAttribute::full_plane;
  }
  else if (name == "gold_plating") {
    m_name = BooleanAttribute::gold_plating;
  }
  else if (name == "mount_hole") {
    m_name = BooleanAttribute::mount_hole;
  }
  else if (name == "net_point") {
    m_name = BooleanAttribute::net_point;
  }
  else if (name == "nomenclature") {
    m_name = BooleanAttribute::nomenclature;
  }
  else if (name == "pattern_fill") {
    m_name = BooleanAttribute::pattern_fill;
  }
  else if (name == "smd") {
    m_name = BooleanAttribute::smd;
  }
  else if (name == "tear_drop") {
    m_name = BooleanAttribute::tear_drop;
  }
  else if (name == "test_point") {
    m_name = BooleanAttribute::test_point;
  }
  else if (name == "tooling_hole") {
    m_name = BooleanAttribute::tooling_hole;
  }
  else {
    errorInvalidAttribute("BooleanAttribute", "name");
    exit(1);
  }
}
