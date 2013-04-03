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
  QString symbol = QString("r%1").arg(l->lineWidth() * 0.5);
  int symNum = odbInsertSymbol(symbol, file.symbolsTable());

  QPointF newLocation = calcTransformedLocation(location, xform);
  QPointF newStart  = newLocation + calcTransformedLocation(m_start, xform);
  QPointF newEnd    = newLocation + calcTransformedLocation(m_end, xform);
  QPointF newCenter = newLocation + calcTransformedLocation(m_center, xform);
  file.featuresList().append(QString("A %1 %2 %3 %4 %5 %6 %7 %8 0 %9\n")
                             .arg(newStart.x())
                             .arg(newStart.y())
                             .arg(newEnd.x())
                             .arg(newEnd.y())
                             .arg(newCenter.x())
                             .arg(newCenter.y())
                             .arg(symNum)
                             .arg(polarity)
                             .arg(m_clockwise? "Y" : "N"));
}
