#include "step.h"
#include "utils.h"

void
Step::initialize(QXmlStreamReader& xml)
{
  m_name = getStringAttribute(xml, "Step", "name");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Attribute") {
        // TODO skipped
      }
      else if (xml.name() == "PadStack") {
        // TODO skipped
      }
      else if (xml.name() == "Route") {
        // TODO skipped
      }
      else if (xml.name() == "Datum") {
        m_datum = QPointF(getDoubleAttribute(xml, "Step", "x"),
                          getDoubleAttribute(xml, "Step", "y"));
      }
      else if (xml.name() == "Profile") {
        m_profile.initialize(xml);
      }
      else if (xml.name() == "StepRepeat") {
        // TODO skipped
      }
      else if (xml.name() == "Package") {
        Package package;
        package.initialize(xml);
        m_packages.append(package);
      }
      else if (xml.name() == "Component") {
        Component component;
        component.initialize(xml);
        m_components.append(component);
      }
      else if (xml.name() == "VplPackage") {
        // TODO skipped
      }
      else if (xml.name() == "VplComponent") {
        // TODO skipped
      }
      else if (xml.name() == "LogicalNet") {
        LogicalNet logicalNet;
        logicalNet.initialize(xml);
        m_logicalNets.append(logicalNet);
      }
      else if (xml.name() == "PhyNetGroup") {
        PhyNetGroup phyNetGroup;
        phyNetGroup.initialize(xml);
        m_phyNetGroups.append(phyNetGroup);
      }
      else if (xml.name() == "LayerFeature") {
        LayerFeature layerFeature;
        layerFeature.initialize(xml);
        m_layerFeatures.append(layerFeature);
      }
      else if (xml.name() == "DfxMeasurementList") {
        // TODO skipped
      }
    }
    else if (isEndElementWithName(xml, "Step")) { // </Step>
      return;
    }
  }
}
