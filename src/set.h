#ifndef __SET_H__
#define __SET_H__

#include <QtCore>
#include "attribute.h"
#include "pad.h"
#include "fiducial.h"
#include "hole.h"
#include "slot.h"
#include "feature.h"
#include "colorgroup.h"
#include "linedescgroup.h"

class Set
{
public:
  void initialize(QXmlStreamReader& xml);
  enum PolarityType { POSITIVE, NEGATIVE };
  enum PadUsageType { TERMINATION, VIA, PLANE, TOOLING_HOLE, MASK, NONE };

private:
  // attributes
  QString *m_net;
  PolarityType m_polarity;
  PadUsageType m_padUsage;
  bool m_testPoint;
  QString *m_geometry;
  bool m_plate;
  QString *m_toolIdRef;

  // nested elements
  QList<Attribute*> m_attributes;
  QList<Pad> m_pads;
  QList<Fiducial*> m_fiducials;
  QList<Hole> m_holes;
  QList<Slot> m_slots;
  QList<Feature*> m_features;
  QList<ColorGroup*> m_colorGroups;
  QList<LineDescGroup*> m_lineDescGroups;
};

#endif
