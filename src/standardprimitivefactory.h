#ifndef __STANDARDPRIMITIVEFACTORY_H__
#define __STANDARDPRIMITIVEFACTORY_H__

#include <QtCore>
#include "standardprimitive.h"
#include "butterfly.h"
#include "circle.h"
#include "contour.h"
#include "diamond.h"
#include "donut.h"
#include "ellipse.h"
#include "hexagon.h"
#include "moire.h"
#include "octagon.h"
#include "oval.h"
#include "rectcenter.h"
#include "rectcham.h"
#include "rectcorner.h"
#include "rectround.h"
#include "thermal.h"
#include "triangle.h"

class StandardPrimitiveFactory
{
public:
  StandardPrimitive* create(QStringRef elementName);
};

#endif
