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
  };
  enum SideType { TOP, BOTTOM, BOTH, INTERNAL, ALL, NONE };
  enum PolarityType { POSITIVE, NEGATIVE };

  // getter
  QString name() { return m_name; }
  LayerFunctionType layerFunction() { return m_layerFunction; }
  QString context(); // "BOARD" or "MISC", from Odb++ job->matrix->matrix
  QString polarity() { return m_polarity == POSITIVE? "POSITIVE" : "NEGATIVE"; }
  QString type();
  bool isTop() { return m_side == TOP; }
  bool isBottom() { return m_side == BOTTOM; }
  QString spanFromLayer() { return (m_span)? m_span->fromLayer() : ""; }
  QString spanToLayer() { return (m_span)? m_span->toLayer() : ""; }

private:
  // member functions
  LayerFunctionType decideLayerFunction(const QString layerFunctionStr);
  SideType decideSide(const QString sideStr);

  // data members
  QString m_name;
  LayerFunctionType m_layerFunction;
  SideType m_side;
  PolarityType m_polarity;
  Span *m_span;
  QList<DrillTool> m_drillTools;
};

#endif
