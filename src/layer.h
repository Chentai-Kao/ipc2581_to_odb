#ifndef __LAYER_H__
#define __LAYER_H__

#include <QtCore>
#include "utils.h"
#include "span.h"
#include "drilltool.h"

class Layer
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_name;
  enum LayerFunctionType {
    ASSEMBLY,
    BOARD_OUTLINE,
    CAPACITIVE,
    COATINGCOND,
    COATINGNONCOND,
    COMPONENT_BOTTOM,
    COMPONENT_TOP,
    CONDFILM,
    CONDFOIL,
    CONDUCTIVE_ADHESIVE,
    CONDUCTOR,
    COURTYARD,
    DIELADHV,
    DIELBASE,
    DIELCORE,
    DIELPREG,
    DOCUMENT,
    DRILL,
    EMBEDDED_COMPONENT,
    FIXTURE,
    GLUE,
    GRAPHIC,
    HOLEFILL,
    LANDPATTERN,
    LEGEND,
    MIXED,
    OTHER,
    PASTEMASK,
    PLANE,
    PROBE,
    RESISTIVE,
    REWORK,
    ROUTE,
    SIGNAL,
    SILKSCREEN,
    SOLDERBUMP,
    SOLDERMASK,
    SOLDERPASTE
  } m_layerFunction;
  enum SideType { TOP, BOTTOM, BOTH, INTERNAL, ALL, NONE } m_side;
  enum PolarityType { POSITIVE, NEGATIVE } m_polarity;
  Span m_span;
  QList<DrillTool> m_drillTools;
};

#endif
