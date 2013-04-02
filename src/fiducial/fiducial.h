#ifndef __FIDUCIAL_H__
#define __FIDUCIAL_H__

#include <QtCore>
#include "standardshape.h"
#include "xform.h"

// Base class of "Fiducial" substitution group:
// BadBoardMark, GlobalFiducial, GoodPanelMark, LocalFiducial
// Note: the four derived classes all have the same data structure,
// so put the data here (and initialize them here)
class Fiducial
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);

private:
  Xform *m_xform;
  QPointF m_location;
  StandardShape *m_standardShape;
};

#endif
