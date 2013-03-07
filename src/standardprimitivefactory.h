#ifndef __STANDARDPRIMITIVEFACTORY_H__
#define __STANDARDPRIMITIVEFACTORY_H__

#include <QtCore>
#include "standardprimitive.h"
#include "spbutterfly.h"
#include "spcircle.h"
#include "spcontour.h"
#include "spdiamond.h"
#include "spdonut.h"
#include "spellipse.h"
#include "sphexagon.h"
#include "spmoire.h"
#include "spoctagon.h"
#include "spoval.h"
#include "sprectcenter.h"
#include "sprectcham.h"
#include "sprectcorner.h"
#include "sprectround.h"
#include "spthermal.h"
#include "sptriangle.h"

class StandardPrimitiveFactory
{
public:
  StandardPrimitive* create(QStringRef elementName);
};

#endif
