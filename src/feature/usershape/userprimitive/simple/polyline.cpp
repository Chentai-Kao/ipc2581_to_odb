#include "polyline.h"
#include "linedescgroupfactory.h"
#include "polystepfactory.h"
#include "globals.h"

void
Polyline::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_lineDescGroup = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "PolyBegin") {
        m_polyBegin.rx() = toMil(
            getDoubleAttribute(xml, "PolyBegin", "x"), units);
        m_polyBegin.ry() = toMil(
            getDoubleAttribute(xml, "PolyBegin", "y"), units);
      }
      else if (isSubstitutionGroupPolyStep(xml.name())) {
        PolyStep *p = PolyStepFactory().create(xml.name());
        p->initialize(xml, units);
        m_polySteps.append(p);
      }
      else if (isSubstitutionGroupLineDescGroup(xml.name())) {
        m_lineDescGroup = LineDescGroupFactory().create(xml.name());
        m_lineDescGroup->initialize(xml, units);
      }
    }
    else if (isEndElementWithName(xml, "Polyline")) { // </Polyline>
      if (m_lineDescGroup == NULL) {
        throw new InvalidElementError("Polyline");
      }
      break;
    }
  }
}

void
Polyline::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  // TODO skipped 
  // throw new NonImplementedError("Polyline::odbOutputLayerFeature");
}
