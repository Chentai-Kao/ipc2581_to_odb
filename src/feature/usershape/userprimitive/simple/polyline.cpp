#include "polyline.h"

void
Polyline::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "PolyBegin") {
        m_polyBegin.rx() = getDoubleAttribute(xml, "PolyBegin", "x");
        m_polyBegin.ry() = getDoubleAttribute(xml, "PolyBegin", "y");
      }
      else if (xml.name() == "PolyStepCurve") {
        PolyStep *polyStep = new PolyStepCurve();
        polyStep->initialize(xml);
        m_polySteps.append(polyStep);
      }
      else if (xml.name() == "PolyStepSegment") {
        PolyStep *polyStep = new PolyStepSegment();
        polyStep->initialize(xml);
        m_polySteps.append(polyStep);
      }
      else if (xml.name() == "LineDesc") {
        m_lineDescGroup = new LineDesc();
        m_lineDescGroup->initialize(xml);
      }
      else if (xml.name() == "LineDescRef") {
        m_lineDescGroup = new LineDescRef();
        m_lineDescGroup->initialize(xml);
      }
    }
    else if (isEndElementWithName(xml, "Polyline")) {
      break;
    }
  }
}

void
Polyline::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    QString polarity,
    QPointF location, Xform *xform)
{
  // TODO skipped 
  // throw new NonImplementedError("Polyline::odbOutputLayerFeature");
}
