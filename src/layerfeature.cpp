#include "layerfeature.h"
#include "utils.h"

void
LayerFeature::initialize(QXmlStreamReader& xml)
{
  m_layerRef = getStringAttribute(xml, "LayerFeature", "layerRef");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Set") {
        Set set;
        set.initialize(xml);
        m_sets.append(set);
      }
    }
    else if (isEndElementWithName(xml, "LayerFeature")) { // </LayerFeature>
      return;
    }
  }
}

void
LayerFeature::odbOutputLayerFeature(QTextStream& out,
      const QHash<QString, StandardPrimitive*>& entryStandards,
      const QHash<QString, UserPrimitive*>&     entryUsers)
{
  /* The feature file has 4 sections:
   * Symbols table, Attribute table, Attribute texts, and Features list.
   * Collect the full information of them, then output to file.
   */
  QList<QString> symbolsTable;
  QList<QString> attributeTable;
  QList<QString> attributeTexts;
  QList<QString> featuresList;

  // collect information
  for (int i = 0; i < m_sets.size(); ++i) {
    m_sets[i].odbOutputLayerFeature(
        symbolsTable, attributeTable, attributeTexts, featuresList,
        entryStandards, entryUsers);
  }

  // output to file
  out << "#\n";
  out << "#Feature symbol names\n";
  out << "#\n";
  for (int i = 0; i < symbolsTable.size(); ++i) {
    out << symbolsTable[i];
  }
  out << "#\n";
  out << "#Feature attribute names\n";
  out << "#\n";
  for (int i = 0; i < attributeTable.size(); ++i) {
    out << attributeTable[i];
  }
  out << "#\n";
  out << "#Feature attribute text strings\n";
  out << "#\n";
  for (int i = 0; i < attributeTexts.size(); ++i) {
    out << attributeTexts[i];
  }
  out << "#\n";
  out << "#Layer features\n";
  out << "#\n";
  for (int i = 0; i < featuresList.size(); ++i) {
    out << featuresList[i];
  }
}
