#include "arc.h"
#include "linedescgroupfactory.h"
#include "utils.h"

void
Arc::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_start = QPointF(toMil(getDoubleAttribute(xml, "Arc", "startX"), units),
                    toMil(getDoubleAttribute(xml, "Arc", "startY"), units));
  m_end = QPointF(toMil(getDoubleAttribute(xml, "Arc", "endX"), units),
                  toMil(getDoubleAttribute(xml, "Arc", "endY"), units));
  m_center = QPointF(toMil(getDoubleAttribute(xml, "Arc", "centerX"), units),
                     toMil(getDoubleAttribute(xml, "Arc", "centerY"), units));
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
  QString symbol = QString("r%1").arg(m_lineDescGroup->lineWidth() * 0.5);
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
