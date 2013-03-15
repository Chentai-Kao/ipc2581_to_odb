#ifndef __LANDPATTERN_H__
#define __LANDPATTERN_H__

#include <QtCore>
#include "pad.h"
#include "target.h"

class LandPattern
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QList<Pad> m_pads;
  QList<Target> m_targets;
};

#endif
