#include "set.h"
#include "utils.h"
#include "error.h"
#include "attributefactory.h"
#include "fiducialfactory.h"
#include "featurefactory.h"
#include "colorgroupfactory.h"
#include "linedescgroupfactory.h"

void
Set::initialize(QXmlStreamReader& xml)
{
  m_net = NULL;
  if (hasAttribute(xml, "net")) {
    m_net = new QString(getStringAttribute(xml, "Set", "net"));
  }
  m_polarity = Set::POSITIVE;
  if (hasAttribute(xml, "polarity")) {
    QString polarity = getStringAttribute(xml, "Set", "polarity");
    if (polarity == "POSITIVE") {
      m_polarity = Set::POSITIVE;
    }
    else if (polarity == "NEGATIVE") {
      m_polarity = Set::NEGATIVE;
    }
    else {
      throw new InvalidAttributeError("Set", "polarity");
    }
  }
  m_padUsage = Set::NONE;
  if (hasAttribute(xml, "padUsage")) {
    QString padUsage = getStringAttribute(xml, "Set", "padUsage");
    if (padUsage == "TERMINATION") {
      m_padUsage = Set::TERMINATION;
    }
    else if (padUsage == "VIA") {
      m_padUsage = Set::VIA;
    }
    else if (padUsage == "PLANE") {
      m_padUsage = Set::PLANE;
    }
    else if (padUsage == "TOOLING_HOLE") {
      m_padUsage = Set::TOOLING_HOLE;
    }
    else if (padUsage == "MASK") {
      m_padUsage = Set::MASK;
    }
    else if (padUsage == "NONE") {
      m_padUsage = Set::NONE;
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
        pad.initialize(xml);
        m_pads.append(pad);
      }
      else if (isSubstitutionGroupFiducial(xml.name())) {
        Fiducial *f = FiducialFactory().create(xml.name());
        f->initialize(xml);
        m_fiducials.append(f);
      }
      else if (xml.name() == "Hole") {
        Hole hole;
        hole.initialize(xml);
        m_holes.append(hole);
      }
      else if (xml.name() == "Slot") {
        Slot slot;
        slot.initialize(xml);
        m_slots.append(slot);
      }
      else if (isSubstitutionGroupFeature(xml.name())) {
        Feature* f = FeatureFactory().create(xml.name());
        f->initialize(xml);
        m_features.append(f);
      }
      else if (isSubstitutionGroupColorGroup(xml.name())) {
        ColorGroup *c = ColorGroupFactory().create(xml.name());
        c->initialize(xml);
        m_colorGroups.append(c);
      }
      else if (isSubstitutionGroupLineDescGroup(xml.name())) {
        LineDescGroup *l = LineDescGroupFactory().create(xml.name());
        l->initialize(xml);
        m_lineDescGroups.append(l);
      }
    }
    else if (isEndElementWithName(xml, "Set")) { // </Set>
      return;
    }
  }
}

void
Set::odbOutputLayerFeature(
    QList<QString>& symbolsTable,
    QList<QString>& attributeTable,
    QList<QString>& attributeTexts,
    QList<QString>& featuresList,
    const QHash<QString, StandardPrimitive*>& entryStandards,
    const QHash<QString, UserPrimitive*>&     entryUsers)
{
  // TODO: m_attributes;

  // TODO: m_pads;
  for (int i = 0; i < m_pads.size(); ++i) {
    QString polarity = (m_polarity == POSITIVE)? "P" : "N";
    m_pads[i].odbOutputLayerFeature(
        symbolsTable, attributeTable, attributeTexts, featuresList, polarity,
        entryStandards);
  }

  // TODO: m_fiducials;

  // TODO: m_holes;

  // TODO: m_slots;

  // TODO: m_features;

  // TODO: m_colorGroups;

  // TODO: m_lineDescGroups;

}
