#include "line.h"
#include "linedescgroupfactory.h"
#include "globals.h"

void
Line::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_start = QPointF(toInch(getDoubleAttribute(xml, "Line", "startX"), units),
                    toInch(getDoubleAttribute(xml, "Line", "startY"), units));
  m_end = QPointF(toInch(getDoubleAttribute(xml, "Line", "endX"), units),
                  toInch(getDoubleAttribute(xml, "Line", "endY"), units));
  // LineDescGroup
  m_lineDescGroup = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (isSubstitutionGroupLineDescGroup(xml.name())) {
        m_lineDescGroup = LineDescGroupFactory().create(xml.name());
        m_lineDescGroup->initialize(xml, units);
      }
    }
    else if (isEndElementWithName(xml, "Line")) { // </Line>
      if (m_lineDescGroup == NULL) {
        throw new InvalidElementError("Line");
      }
      return;
    }
  }
}

void
Line::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString refId = m_lineDescGroup->refId();
  LineDescGroup *l;
  if (refId == "") { // not a reference to others
    l = m_lineDescGroup;
  }
  else if (g_entryLineDescs.contains(refId)) { // a reference to LineDescGroup 
    l = &g_entryLineDescs[refId];
  }
  else { // cannot find it in dictionary
    throw new InvalidIdError(refId);
  }
  QString symbol = QString("%1%2") // square (e.g. s5) or round (e.g. r2)
                   .arg(l->endType())
                   .arg(l->lineWidth().mil());
  int symNum = odbInsertSymbol(symbol, file.symbolsTable());

  QPointF newLocation = calcTransformedLocation(location, xform);
  QPointF newStart    = newLocation + calcTransformedLocation(m_start, xform);
  QPointF newEnd      = newLocation + calcTransformedLocation(m_end, xform);
  file.featuresList().append(QString("L %1 %2 %3 %4 %5 %6 0\n")
                             .arg(newStart.x())
                             .arg(newStart.y())
                             .arg(newEnd.x())
                             .arg(newEnd.y())
                             .arg(symNum)
                             .arg(polarity));
}
