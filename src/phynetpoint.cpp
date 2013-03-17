#include "phynetpoint.h"
#include "utils.h"
#include "standardshapefactory.h"

void
PhyNetPoint::initialize(QXmlStreamReader& xml)
{
  m_point = QPointF(getDoubleAttribute(xml, "PhyNetPoint", "x"),
                    getDoubleAttribute(xml, "PhyNetPoint", "y"));
  m_layerRef = getStringAttribute(xml, "PhyNetPoint", "layerRef");

  QString netNode = getStringAttribute(xml, "PhyNetPoint", "netNode");
  if (netNode == "END") {
    m_netNode = PhyNetPoint::END;
  }
  else if (netNode == "MIDDLE") {
    m_netNode = PhyNetPoint::MIDDLE;
  }
  else {
    errorInvalidAttribute("PhyNetPoint", "netNode");
  }

  QString exposure = getStringAttribute(xml, "PhyNetPoint", "exposure");
  if (exposure == "EXPOSED") {
    m_exposure = PhyNetPoint::EXPOSED;
  }
  else if (exposure == "COVERED_PRIMARY") {
    m_exposure = PhyNetPoint::COVERED_PRIMARY;
  }
  else if (exposure == "COVERED_SECONDARY") {
    m_exposure = PhyNetPoint::COVERED_SECONDARY;
  }
  else if (exposure == "COVERED") {
    m_exposure = PhyNetPoint::COVERED;
  }
  else {
    errorInvalidAttribute("PhyNetPoint", "exposure");
  }

  m_layerIndex = NULL;
  if (hasAttribute(xml, "layerIndex")) {
    m_layerIndex =
        new QString(getStringAttribute(xml, "PhyNetPoint", "layerIndex"));
  }

  m_comment = NULL;
  if (hasAttribute(xml, "comment")) {
    m_comment = new QString(getStringAttribute(xml, "PhyNetPoint", "comment"));
  }

  m_via = NULL;
  if (hasAttribute(xml, "via")) {
    m_via = new bool(getBoolAttribute(xml, "via"));
  }

  m_fiducial = NULL;
  if (hasAttribute(xml, "fiducial")) {
    m_fiducial = new bool(getBoolAttribute(xml, "fiducial"));
  }

  m_test = NULL;
  if (hasAttribute(xml, "test")) {
    m_test = new bool(getBoolAttribute(xml, "test"));
  }

  m_staggerX = NULL;
  if (hasAttribute(xml, "staggerX")) {
    m_staggerX = new qreal(getDoubleAttribute(xml, "PhyNetPoint", "staggerX"));
  }

  m_staggerY = NULL;
  if (hasAttribute(xml, "staggerY")) {
    m_staggerY = new qreal(getDoubleAttribute(xml, "PhyNetPoint", "staggerY"));
  }

  m_staggerRadius = NULL;
  if (hasAttribute(xml, "staggerRadius")) {
    m_staggerRadius =
        new qreal(getDoubleAttribute(xml, "PhyNetPoint", "staggerRadius"));
  }

  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (isSubstitutionGroupStandardShape(xml.name())) {
        m_standardShape = StandardShapeFactory().create(xml.name());
        if (m_standardShape == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
        m_standardShape->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "PhyNetPoint")) { // </PhyNetPoint>
      return;
    }
  }
}
