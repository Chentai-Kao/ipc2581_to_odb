#include "arc.h"
#include "linedescgroupfactory.h"
#include "utils.h"
#include "globals.h"

void
Arc::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_start = QPointF(toInch(getDoubleAttribute(xml, "Arc", "startX"), units),
                    toInch(getDoubleAttribute(xml, "Arc", "startY"), units));
  m_end = QPointF(toInch(getDoubleAttribute(xml, "Arc", "endX"), units),
                  toInch(getDoubleAttribute(xml, "Arc", "endY"), units));
  m_center = QPointF(toInch(getDoubleAttribute(xml, "Arc", "centerX"), units),
                     toInch(getDoubleAttribute(xml, "Arc", "centerY"), units));
  m_clockwise = getBoolAttribute(xml, "clockwise");
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
    else if (isEndElementWithName(xml, "Arc")) { // </Arc>
      if (m_lineDescGroup == NULL) {
        throw new InvalidElementError("Arc");
      }
      return;
    }
  }
}

void
Arc::odbOutputLayerFeature(
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
  QString symbol = QString("r%1").arg(lw);
  int symNum = odbInsertSymbol(symbol, file.symbolsTable());

  // determine the path
  QPointF newStart  = applyXform(xform, m_start);
  QPointF newEnd    = applyXform(xform, m_end);
  QPointF newCenter = applyXform(xform, m_center);
  // if Xform contains "mirror", then the clockwise will reverse
  bool cw = m_clockwise;
  if (xform && xform->mirror()) {
    cw = !cw;
  }
  file.featuresList().append(QString("A %1 %2 %3 %4 %5 %6 %7 %8 0 %9\n")
                             .arg(location.x() + newStart.x())
                             .arg(location.y() + newStart.y())
                             .arg(location.x() + newEnd.x())
                             .arg(location.y() + newEnd.y())
                             .arg(location.x() + newCenter.x())
                             .arg(location.y() + newCenter.y())
                             .arg(symNum)
                             .arg(polarity)
                             .arg(cw? "Y" : "N"));
}
