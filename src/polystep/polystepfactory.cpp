#include "polystepfactory.h"
#include "polystepcurve.h"
#include "polystepsegment.h"
#include "error.h"

PolyStep*
PolyStepFactory::create(QStringRef elementName)
{
  if (elementName == "PolyStepCurve") {
    return new PolyStepCurve();
  }
  else if (elementName == "PolyStepSegment") {
    return new PolyStepSegment();
  }
  throw new InvalidElementError(elementName);
}
