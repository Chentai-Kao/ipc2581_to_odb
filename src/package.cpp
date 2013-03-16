#include "package.h"
#include "utils.h"

void
Package::initialize(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "Package", "name");
  m_type = decidePackageType(xml);
  m_pinOne = NULL;
  if (hasAttribute(xml, "pinOne")) {
    m_pinOne = new QString(getStringAttribute(xml, "Package", "pinOne"));
  }
  m_height = NULL;
  if (hasAttribute(xml, "height")) {
    m_height =
        new qreal(getNonNegativeDoubleAttribute(xml, "Package", "height"));
  }

  m_landPattern = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Outline") {
        m_outline.initialize(xml);
      }
      else if (xml.name() == "LandPattern") {
        m_landPattern = new LandPattern();
        m_landPattern->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "Package")) { // </Package>
      return;
    }
  }
}

Package::PackageType
Package::decidePackageType(QXmlStreamReader& xml)
{
  QString packageType = getStringAttribute(xml, "Package", "type");
  if (packageType == "AXIAL_LEADED") {
    return Package::AXIAL_LEADED;
  }
  else if (packageType == "BARE_DIE") {
    return Package::BARE_DIE;
  }
  else if (packageType == "CERAMIC_BGA") {
    return Package::CERAMIC_BGA;
  }
  else if (packageType == "CERAMIC_DIP") {
    return Package::CERAMIC_DIP;
  }
  else if (packageType == "CERAMIC_FLATPACK") {
    return Package::CERAMIC_FLATPACK;
  }
  else if (packageType == "CERAMIC_QUAD_FLATPACK") {
    return Package::CERAMIC_QUAD_FLATPACK;
  }
  else if (packageType == "CERAMIC_SIP") {
    return Package::CERAMIC_SIP;
  }
  else if (packageType == "CHIP") {
    return Package::CHIP;
  }
  else if (packageType == "CHIP_SCALE") {
    return Package::CHIP_SCALE;
  }
  else if (packageType == "CHOKE_SWITCH_SM") {
    return Package::CHOKE_SWITCH_SM;
  }
  else if (packageType == "COIL") {
    return Package::COIL;
  }
  else if (packageType == "CONNECTOR_SM") {
    return Package::CONNECTOR_SM;
  }
  else if (packageType == "CONNECTOR_TH") {
    return Package::CONNECTOR_TH;
  }
  else if (packageType == "EMBEDDED") {
    return Package::EMBEDDED;
  }
  else if (packageType == "FINEPITCH_BGA") {
    return Package::FINEPITCH_BGA;
  }
  else if (packageType == "FLIPCHIP") {
    return Package::FLIPCHIP;
  }
  else if (packageType == "HERMETIC_HYBRID") {
    return Package::HERMETIC_HYBRID;
  }
  else if (packageType == "LEADLESS_CERAMIC_CHIP_CARRIER") {
    return Package::LEADLESS_CERAMIC_CHIP_CARRIER;
  }
  else if (packageType == "MCM") {
    return Package::MCM;
  }
  else if (packageType == "MELF") {
    return Package::MELF;
  }
  else if (packageType == "MOLDED") {
    return Package::MOLDED;
  }
  else if (packageType == "NETWORK") {
    return Package::NETWORK;
  }
  else if (packageType == "OTHER") {
    return Package::OTHER;
  }
  else if (packageType == "PGA") {
    return Package::PGA;
  }
  else if (packageType == "PLASTIC_BGA") {
    return Package::PLASTIC_BGA;
  }
  else if (packageType == "PLASTIC_CHIP_CARRIER") {
    return Package::PLASTIC_CHIP_CARRIER;
  }
  else if (packageType == "PLASTIC_DIP") {
    return Package::PLASTIC_DIP;
  }
  else if (packageType == "PLASTIC_SIP") {
    return Package::PLASTIC_SIP;
  }
  else if (packageType == "POWER_TRANSISTOR") {
    return Package::POWER_TRANSISTOR;
  }
  else if (packageType == "RADIAL_LEADED") {
    return Package::RADIAL_LEADED;
  }
  else if (packageType == "RECTANGULAR_QUAD_FLATPACK") {
    return Package::RECTANGULAR_QUAD_FLATPACK;
  }
  else if (packageType == "RELAY_SM") {
    return Package::RELAY_SM;
  }
  else if (packageType == "RELAY_TH") {
    return Package::RELAY_TH;
  }
  else if (packageType == "SOD123") {
    return Package::SOD123;
  }
  else if (packageType == "SOIC") {
    return Package::SOIC;
  }
  else if (packageType == "SOJ") {
    return Package::SOJ;
  }
  else if (packageType == "SOPIC") {
    return Package::SOPIC;
  }
  else if (packageType == "SOT143") {
    return Package::SOT143;
  }
  else if (packageType == "SOT23") {
    return Package::SOT23;
  }
  else if (packageType == "SOT52") {
    return Package::SOT52;
  }
  else if (packageType == "SOT89") {
    return Package::SOT89;
  }
  else if (packageType == "SQUARE_QUAD_FLATPACK") {
    return Package::SQUARE_QUAD_FLATPACK;
  }
  else if (packageType == "SSOIC") {
    return Package::SSOIC;
  }
  else if (packageType == "SWITCH_TH") {
    return Package::SWITCH_TH;
  }
  else if (packageType == "TANTALUM") {
    return Package::TANTALUM;
  }
  else if (packageType == "TO_TYPE") {
    return Package::TO_TYPE;
  }
  else if (packageType == "TRANSFORMER") {
    return Package::TRANSFORMER;
  }
  else if (packageType == "TRIMPOT_SM") {
    return Package::TRIMPOT_SM;
  }
  else if (packageType == "TRIMPOT_TH") {
    return Package::TRIMPOT_TH;
  }
  errorInvalidAttribute("Package", "type");
  exit(1);
}
