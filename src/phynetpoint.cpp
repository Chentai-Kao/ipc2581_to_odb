#include "phynetpoint.h"
#include "utils.h"
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
#include "polygon.h"
#include "rectcenter.h"
#include "rectcham.h"
#include "rectcorner.h"
#include "rectround.h"
#include "standardprimitive.h"
#include "standardprimitiveref.h"
#include "thermal.h"
#include "triangle.h"

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
      if (xml.name() == "StandardPrimitiveRef") {
        m_standardShape = new StandardPrimitiveRef();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Butterfly") {
        m_standardShape = new Butterfly();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Circle") {
        m_standardShape = new Circle();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Contour") {
        m_standardShape = new Contour();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Diamond") {
        m_standardShape = new Diamond();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Donut") {
        m_standardShape = new Donut();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Ellipse") {
        m_standardShape = new Ellipse();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Hexagon") {
        m_standardShape = new Hexagon();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Moire") {
        m_standardShape = new Moire();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Octagon") {
        m_standardShape = new Octagon();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Oval") {
        m_standardShape = new Oval();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "RectCenter") {
        m_standardShape = new RectCenter();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "RectCham") {
        m_standardShape = new RectCham();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "RectCorner") {
        m_standardShape = new RectCorner();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "RectRound") {
        m_standardShape = new RectRound();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Thermal") {
        m_standardShape = new Thermal();
        m_standardShape->initialize(xml);
      }
      else if (xml.name() == "Triangle") {
        m_standardShape = new Triangle();
        m_standardShape->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "PhyNetPoint")) { // </PhyNetPoint>
      return;
    }
  }
}
