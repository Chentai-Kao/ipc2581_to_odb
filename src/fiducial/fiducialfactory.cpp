#include "fiducialfactory.h"
#include "badboardmark.h"
#include "globalfiducial.h"
#include "goodpanelmark.h"
#include "localfiducial.h"

Fiducial*
FiducialFactory::create(QStringRef elementName)
{
  if (elementName == "BadBoardMark") {
    return new BadBoardMark();
  }
  else if (elementName == "GlobalFiducial") {
    return new GlobalFiducial();
  }
  else if (elementName == "GoodPanelMark") {
    return new GoodPanelMark();
  }
  else if (elementName == "LocalFiducial") {
    return new LocalFiducial();
  }
  return NULL;
}
