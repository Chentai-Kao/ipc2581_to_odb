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
  // get the line description
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

  // determine the line width and its symbol
  qreal lw = l->lineWidth().mil();
  if (xform) { // apply scale if needed
    lw *= xform->scale();
  }
  QString symbol = QString("%1%2") // square (e.g. s5) or round (e.g. r2)
                           .arg(l->endType())
                           .arg(ROUND(lw));
  int symNum = odbInsertSymbol(symbol, file.symbolsTable());

  // determine the path
  QPointF newStart = applyXform(xform, m_start);
  QPointF newEnd   = applyXform(xform, m_end);
  file.featuresList().append(QString("L %1 %2 %3 %4 %5 %6 0\n")
                             .arg(saveQreal(location.x() + newStart.x()))
                             .arg(saveQreal(location.y() + newStart.y()))
                             .arg(saveQreal(location.x() + newEnd.x()))
                             .arg(saveQreal(location.y() + newEnd.y()))
                             .arg(symNum)
                             .arg(polarity));
}
