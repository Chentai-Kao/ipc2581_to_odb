#include "pad.h"
#include "standardshapefactory.h"
#include "error.h"
#include "globals.h"

void
Pad::initialize(QXmlStreamReader& xml, UnitsType units)
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
        m_location = QPointF(
            toInch(getDoubleAttribute(xml, "Location", "x"), units),
            toInch(getDoubleAttribute(xml, "Location", "y"), units));
      }
      else if (isSubstitutionGroupStandardShape(xml.name())) {
        m_standardShape = StandardShapeFactory().create(xml.name());
        m_standardShape->initialize(xml, units);
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

void
Pad::odbOutputLayerFeature(OdbFeatureFile& file, QString polarity)
{
  // if the shape is a reference, find it in the list
  QString refId = m_standardShape->refId();
  StandardShape *s;
  if (refId == "") {
    s = m_standardShape;
  }
  else if (g_entryStandards.contains(refId)) {
    s = g_entryStandards[refId];
  }
  else {
    throw new InvalidIdError(refId);
  }

  // call the shape to output
  s->odbOutputLayerFeature(file, polarity, m_location, m_xform);
}
