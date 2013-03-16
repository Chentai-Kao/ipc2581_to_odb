#include "fiducial.h"
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
Fiducial::initialize(QXmlStreamReader& xml)
{
  m_xform = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Xform") {
        m_xform = new Xform();
        m_xform->initialize(xml);
      }
      else if (xml.name() == "Location") {
        m_location = QPointF(getDoubleAttribute(xml, "Fiducial", "x"),
                             getDoubleAttribute(xml, "Fiducial", "y"));
      }
      else if (xml.name() == "StandardPrimitiveRef") {
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
    else if (isEndElementWithName(xml, "Fiducial")) { // </Fiducial>
      return;
    }
  }
}
