#include "step.h"
#include "utils.h"
#include "attributefactory.h"
#include "error.h"

void
Step::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_name = getStringAttribute(xml, "Step", "name");
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (isSubstitutionGroupAttribute(xml.name())) {
        Attribute *a = AttributeFactory().create(xml.name());
        a->initialize(xml);
        m_attributes.append(a);
      }
      else if (xml.name() == "PadStack") {
// TODO skipped
        //throw new NonImplementedError("PadStack");
      }
      else if (xml.name() == "Route") {
// TODO skipped
        //throw new NonImplementedError("Route");
      }
      else if (xml.name() == "Datum") {
        m_datum = QPointF(
            toInch(getDoubleAttribute(xml, "Step", "x"), units),
            toInch(getDoubleAttribute(xml, "Step", "y"), units));
      }
      else if (xml.name() == "Profile") {
        m_profile.initialize(xml, units);
      }
      else if (xml.name() == "StepRepeat") {
// TODO skipped
        //throw new NonImplementedError("StepRepeat");
      }
      else if (xml.name() == "Package") {
        Package package;
        package.initialize(xml, units);
        m_packages.append(package);
      }
      else if (xml.name() == "Component") {
        Component component;
        component.initialize(xml);
        m_components.append(component);
      }
      else if (xml.name() == "VplPackage") {
// TODO skipped
        //throw new NonImplementedError("VplPackage");
      }
      else if (xml.name() == "VplComponent") {
// TODO skipped
        //throw new NonImplementedError("VplComponent");
      }
      else if (xml.name() == "LogicalNet") {
        LogicalNet logicalNet;
        logicalNet.initialize(xml);
        m_logicalNets.append(logicalNet);
      }
      else if (xml.name() == "PhyNetGroup") {
        PhyNetGroup phyNetGroup;
        phyNetGroup.initialize(xml, units);
        m_phyNetGroups.append(phyNetGroup);
      }
      else if (xml.name() == "LayerFeature") {
        LayerFeature layerFeature;
        layerFeature.initialize(xml, units);
        m_layerFeatures.append(layerFeature);
      }
      else if (xml.name() == "DfxMeasurementList") {
// TODO skipped
        //throw new NonImplementedError("DfxMeasurementList");
      }
    }
    else if (isEndElementWithName(xml, "Step")) { // </Step>
      return;
    }
  }
}

void
Step::odbOutputLayerFeature(QTextStream& out, const QString layerName)
{
  // find the specific layer, and let it output
  for (int i = 0; i < m_layerFeatures.size(); ++i) {
    if (m_layerFeatures[i].layerRef() == layerName) {
      m_layerFeatures[i].odbOutputLayerFeature(out);
      break;
    }
  }
}
