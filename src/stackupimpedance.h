#ifndef __STACKUPIMPEDANCE_H__
#define __STACKUPIMPEDANCE_H__

#include <QtCore>
#include "xform.h"
#include "outline.h"
#include "polyline.h"
#include "contour.h"
#include "utils.h"

class StackupImpedance
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);
  enum StackImpedanceType {
    MICROSTRIP,
    DIFFERENTIAL_PAIR,
    EMBEDDED_MICROSTRIP,
    EDGE_COUPLED_STRIPLINE,
    DECOUPLED_EMBEDDED_MICROSTRIP,
    RAMBUS,
    COPLANAR_WAVEGUIDE_MICROSTRIP,
    COPLANAR_WAVEGUIDE_STRIPLINE,
    EDGE_COUPLED_COPLANAR_WAVEGUIDE_STRIPLINE,
    EDGE_COUPLED_COPLANAR_WAVEGUIDE_MICROSTRIP,
    NONE 
  };

private:
  // member functions
  StackImpedanceType decideStackImpedanceType(QString type);

  // data members
  qreal m_value;
  StackImpedanceType m_type;
  qreal m_tolPlus;
  qreal m_tolMinus;
  QString m_introduction;
  Xform *m_xform;
  QPointF m_location;
  QList<Polyline> m_polylines;
  QList<Contour> m_contours;
  QList<QString> m_layerRefs;
};

#endif
