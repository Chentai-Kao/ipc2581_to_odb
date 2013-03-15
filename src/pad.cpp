#include "pad.h"

void
Pad::initialize(QXmlStreamReader& xml)
{
  m_xform = NULL;
  m_pinRef = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Xform") {
        m_xform = new Xform();
        m_xform->initialize(xml);
      }
      else if (xml.name() == "Location") {
        m_location = QPointF(getDoubleAttribute(xml, "Location", "x"),
                             getDoubleAttribute(xml, "Location", "y"));
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
      else if (xml.name() == "PinRef") {
        m_pinRef = new PinRef();
        m_pinRef->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "Pad")) { // </Pad>
      return;
    }
  }
}
