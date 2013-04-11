#include "butterfly.h"
#include "error.h"

void
Butterfly::initialize(QXmlStreamReader& xml, UnitsType units)
{
  // shape
  QString shape = getStringAttribute(xml, "Butterfly", "shape");
  if (shape == "ROUND") {
    m_shape = ROUND;
  }
  else if (shape == "SQUARE") {
    m_shape = SQUARE;
  }
  else {
    throw new InvalidAttributeError("Butterfly", "shape");
  }
  // diameter and side
  if (m_shape == ROUND) {
    m_diameter = toMil(
        getNonNegativeDoubleAttribute(xml, "Butterfly", "diameter"), units);
  }
  else if (m_shape == SQUARE) {
    m_side = toMil(
        getNonNegativeDoubleAttribute(xml, "Butterfly", "side"), units);
  }
}

void
Butterfly::odbOutputLayerFeature(
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  QString symbol;
  if (m_shape == ROUND) { // bfr<d>
    symbol = QString("bfr%1").arg(m_diameter);
  }
  else { // bfs<s>
    symbol = QString("bfs%1").arg(m_side);
  }

  int symNum = odbInsertSymbol(symbol, file.symbolsTable());
  QPointF newLocation = calcTransformedLocation(location, xform);
  int orient = odbDecideOrient(xform);
  file.featuresList().append(QString("P %1 %2 %3 %4 0 %5\n")
                              .arg(newLocation.x())
                              .arg(newLocation.y())
                              .arg(symNum)
                              .arg(polarity)
                              .arg(orient));
}
