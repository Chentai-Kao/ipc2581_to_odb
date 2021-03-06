#ifndef __PACKAGE_G__
#define __PACKAGE_G__

#include <QtCore>
#include "outline.h"
#include "landpattern.h"
//#include "silkscreen.h"
//#include "assemblydrawing.h"
//#include "pin.h"
#include "utils.h"

class Package
{
public:
  void initialize(QXmlStreamReader& xml, UnitsType units);
  enum PackageType {
    AXIAL_LEADED,
    BARE_DIE,
    CERAMIC_BGA,
    CERAMIC_DIP,
    CERAMIC_FLATPACK,
    CERAMIC_QUAD_FLATPACK,
    CERAMIC_SIP,
    CHIP,
    CHIP_SCALE,
    CHOKE_SWITCH_SM,
    COIL,
    CONNECTOR_SM,
    CONNECTOR_TH,
    EMBEDDED,
    FINEPITCH_BGA,
    FLIPCHIP,
    HERMETIC_HYBRID,
    LEADLESS_CERAMIC_CHIP_CARRIER,
    MCM,
    MELF,
    MOLDED,
    NETWORK,
    OTHER,
    PGA,
    PLASTIC_BGA,
    PLASTIC_CHIP_CARRIER,
    PLASTIC_DIP,
    PLASTIC_SIP,
    POWER_TRANSISTOR,
    RADIAL_LEADED,
    RECTANGULAR_QUAD_FLATPACK,
    RELAY_SM,
    RELAY_TH,
    SOD123,
    SOIC,
    SOJ,
    SOPIC,
    SOT143,
    SOT23,
    SOT52,
    SOT89,
    SQUARE_QUAD_FLATPACK,
    SSOIC,
    SWITCH_TH,
    TANTALUM,
    TO_TYPE,
    TRANSFORMER,
    TRIMPOT_SM,
    TRIMPOT_TH
  };

private:
  // member functions
  PackageType decidePackageType(QXmlStreamReader& xml);

  // data members
  QString m_name;
  PackageType m_type;
  QString *m_pinOne;
  qreal *m_height;
  Outline m_outline;
  LandPattern *m_landPattern;
};

#endif
