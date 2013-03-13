#ifndef __STACKUPIMPEDANCE_H__
#define __STACKUPIMPEDANCE_H__

#include <QtCore>
//#include "xform.h"
#include "outline.h"
#include "modification.h"

class StackupImpedance
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  qreal m_value;
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
  } m_type;
  qreal m_tolPlus;
  qreal m_tolMinus;
  QString m_introduction;
//  Xform m_xform;
  QPointF m_location;
  Outline m_outline;
  QList<Modification> m_modifications;
};

#endif
