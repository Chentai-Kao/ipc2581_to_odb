#include "polyline.h"
#include "linedescgroupfactory.h"
#include "polystepfactory.h"
#include "globals.h"
#include "polygon.h"

void
Polyline::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_lineDescGroup = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "PolyBegin") {
        m_polyBegin.rx() = toInch(
            getDoubleAttribute(xml, "PolyBegin", "x"), units);
        m_polyBegin.ry() = toInch(
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
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  // construct a customized polygon (shape not closed)
  Polygon polygon;
  polygon.setPolyBegin(m_polyBegin);
  polygon.setPolySteps(m_polySteps);

  // converts all PolyStep to Arc and Line
  QList<Simple*> arcLineList;
  polygon.toArcLine(arcLineList, m_lineDescGroup);

  // print all Arc and Line
  for (int i = 0; i < arcLineList.size(); ++i) {
    arcLineList[i]->odbOutputLayerFeature(file, polarity, location, xform);
  }
}
