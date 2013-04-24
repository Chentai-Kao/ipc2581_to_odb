#include "contour.h"

void
Contour::initialize(QXmlStreamReader& xml, UnitsType units)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Polygon") {
        m_polygon.initialize(xml, units);
      }
      else if (xml.name() == "Cutout") {
        Polygon polygon;
        polygon.initialize(xml, units);
        m_cutouts.append(polygon);
      }
    }
    else if (isEndElementWithName(xml, "Contour") || // </Contour> the end
             isEndElementWithName(xml, "Profile")) { // other possible name
      return;
    }
  }
}

void
Contour::odbOutputLayerFeature(
    OdbFeatureFile& file, QString polarity,
    QPointF location, Xform *xform)
{
  // start the Surface description
  file.featuresList().append(QString("S %1 0\n").arg(polarity));

  // output island and hole
  m_polygon.odbOutputLayerFeature(file, location, xform, POLYGON);
  for (int i = 0; i < m_cutouts.size(); ++i) {
    m_cutouts[i].odbOutputLayerFeature(
        file, location, xform, CUTOUT);
  }
  file.featuresList().append(QString("SE\n"));
}

void
Contour::odbOutputProfile(OdbFeatureFile& file)
{
  file.featuresList().append(QString("S %1 0\n").arg("P"));
  // output island only
  m_polygon.odbOutputLayerFeature(file, QPointF(0, 0), NULL, POLYGON);
  file.featuresList().append(QString("SE\n"));
}
