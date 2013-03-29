#include "contour.h"

void
Contour::initialize(QXmlStreamReader& xml)
{
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Polygon") {
        m_polygon.initialize(xml);
      }
      else if (xml.name() == "Cutout") {
        Polygon polygon;
        polygon.initialize(xml);
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
    OdbFeatureFile& file,
    QString polarity,
    QPointF location, Xform *xform)
{
  m_polygon.odbOutputLayerFeature(
      file,
      polarity, location, xform, POLYGON);

  // cutout has inverse polarity
  QString invPolarity = (polarity == "P")? "N" : "P";
  for (int i = 0; i < m_cutouts.size(); ++i) {
    m_cutouts[i].odbOutputLayerFeature(
        file,
        invPolarity, location, xform, CUTOUT);
  }
}
