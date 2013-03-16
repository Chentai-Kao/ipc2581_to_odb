#ifndef __SET_H__
#define __SET_H__

#include <QtCore>

class Set
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  // attributes
  QString *m_net;
  enum PolarityType { POSITIVE, NEGATIVE } m_polarity;
  enum PadUsageType {
    TERMINATION
     VIA,
     PLANE,
     TOOLING_HOLE,
     MASK,
     NONE
  } m_padUsage;
  bool m_testPoint;
  QString *m_geometry;
  bool m_plate;
  QString *m_toolIdRef;
  // nested elements
  
};

#endif
