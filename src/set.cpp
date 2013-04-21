#include "set.h"
#include "utils.h"
#include "error.h"
#include "attributefactory.h"
#include "fiducialfactory.h"
#include "featurefactory.h"
#include "colorgroupfactory.h"
#include "linedescgroupfactory.h"
#include "featuresgroup.h"

void
Set::initialize(QXmlStreamReader& xml, UnitsType units)
{
  m_net = NULL;
  if (hasAttribute(xml, "net")) {
    m_net = new QString(getStringAttribute(xml, "Set", "net"));
  }
  m_polarity = POSITIVE;
  if (hasAttribute(xml, "polarity")) {
    QString polarity = getStringAttribute(xml, "Set", "polarity");
    if (polarity == "POSITIVE") {
      m_polarity = POSITIVE;
    }
    else if (polarity == "NEGATIVE") {
      m_polarity = NEGATIVE;
    }
    else {
      throw new InvalidAttributeError("Set", "polarity");
    }
  }
  m_padUsage = NONE;
  if (hasAttribute(xml, "padUsage")) {
    QString padUsage = getStringAttribute(xml, "Set", "padUsage");
    if (padUsage == "TERMINATION") {
      m_padUsage = TERMINATION;
    }
    else if (padUsage == "VIA") {
      m_padUsage = VIA;
    }
    else if (padUsage == "PLANE") {
      m_padUsage = PLANE;
    }
    else if (padUsage == "TOOLING_HOLE") {
      m_padUsage = TOOLING_HOLE;
    }
    else if (padUsage == "MASK") {
      m_padUsage = MASK;
    }
    else if (padUsage == "NONE") {
      m_padUsage = NONE;
    }
    else {
      throw new InvalidAttributeError("Set", "padUsage");
    }
  }

  m_testPoint = false;
  if (hasAttribute(xml, "testPoint")) {
    m_testPoint = getBoolAttribute(xml, "testPoint");
  }
  m_geometry = NULL;
  if (hasAttribute(xml, "geometry")) {
    m_geometry = new QString(getStringAttribute(xml, "Set", "geometry"));
  }
  m_plate = false;
  if (hasAttribute(xml, "plate")) {
    m_plate = getBoolAttribute(xml, "plate");
  }
  m_toolIdRef = NULL;
  if (hasAttribute(xml, "toolIdRef")) {
    m_toolIdRef = new QString(getStringAttribute(xml, "Set", "toolIdRef"));
  }

  // nested elements
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (isSubstitutionGroupAttribute(xml.name())) {
        Attribute *a = AttributeFactory().create(xml.name());
        a->initialize(xml);
        m_attributes.append(a);
      }
      else if (xml.name() == "Pad") {
        Pad pad;
        pad.initialize(xml, units);
        m_pads.append(pad);
      }
      else if (isSubstitutionGroupFiducial(xml.name())) {
        Fiducial *f = FiducialFactory().create(xml.name());
        f->initialize(xml, units);
        m_fiducials.append(f);
      }
      else if (xml.name() == "Hole") {
        Hole hole;
        hole.initialize(xml, units);
        m_holes.append(hole);
      }
      else if (xml.name() == "Slot") {
        Slot slot;
        slot.initialize(xml, units);
        m_slots.append(slot);
      }
      else if (xml.name() == "Features") {
        Features features;
        features.initialize(xml, units);
        m_featureses.append(features);
      }
      else if (isSubstitutionGroupColorGroup(xml.name())) {
        ColorGroup *c = ColorGroupFactory().create(xml.name());
        c->initialize(xml);
        m_colorGroups.append(c);
      }
      else if (isSubstitutionGroupLineDescGroup(xml.name())) {
        LineDescGroup *l = LineDescGroupFactory().create(xml.name());
        l->initialize(xml, units);
        m_lineDescGroups.append(l);
      }
    }
    else if (isEndElementWithName(xml, "Set")) { // </Set>
      return;
    }
  }
}

void
Set::odbOutputLayerFeature(OdbFeatureFile& file)
{
  QString polarity = (m_polarity == POSITIVE)? "P" : "N";

  // TODO: m_attributes;

  // TODO: m_pads;
  for (int i = 0; i < m_pads.size(); ++i) {
    m_pads[i].odbOutputLayerFeature(file, polarity);
  }

  // TODO: m_fiducials;

  // TODO: m_holes;
  for (int i = 0; i < m_holes.size(); ++i) {
    m_holes[i].odbOutputLayerFeature(file, polarity);
  }

  // TODO: m_slots;

  // TODO: m_featureses;
  for (int i = 0; i < m_featureses.size(); ++i) {
    m_featureses[i].odbOutputLayerFeature(file, polarity);
  }

  // TODO: m_colorGroups;

  // TODO: m_lineDescGroups;

}
