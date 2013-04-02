#include "layerfeature.h"
#include "utils.h"
#include "odbfeaturefile.h"

void
LayerFeature::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_layerRef = getStringAttribute(xml, "LayerFeature", "layerRef");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Set") {
        Set set;
        set.initialize(xml, units);
        m_sets.append(set);
      }
    }
    else if (isEndElementWithName(xml, "LayerFeature")) { // </LayerFeature>
      return;
    }
  }
}

void
LayerFeature::odbOutputLayerFeature(QTextStream& out)
{
  /* The feature file has 4 sections:
   * Symbols table, Attribute table, Attribute texts, and Features list.
   * Collect the full information of them, then output to file.
   */
  OdbFeatureFile file;

  // collect information
  for (int i = 0; i < m_sets.size(); ++i) {
    m_sets[i].odbOutputLayerFeature(file);
  }

  // output to file
  out << "#\n";
  out << "#Feature symbol names\n";
  out << "#\n";
  for (int i = 0; i < file.symbolsTable().size(); ++i) {
    out << QString("$%1 %2\n")
                   .arg(i)
                   .arg(file.symbolsTable()[i]);
  }
  out << "#\n";
  out << "#Feature attribute names\n";
  out << "#\n";
  for (int i = 0; i < file.attributeTable().size(); ++i) {
    out << file.attributeTable()[i];
  }
  out << "#\n";
  out << "#Feature attribute text strings\n";
  out << "#\n";
  for (int i = 0; i < file.attributeTexts().size(); ++i) {
    out << file.attributeTexts()[i];
  }
  out << "#\n";
  out << "#Layer features\n";
  out << "#\n";
  for (int i = 0; i < file.featuresList().size(); ++i) {
    out << file.featuresList()[i];
  }
}
