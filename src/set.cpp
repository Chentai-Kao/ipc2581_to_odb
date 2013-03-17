#include "set.h"
#include "utils.h"
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
      errorInvalidAttribute("Set", "polarity");
      exit(1);
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
      errorInvalidAttribute("Set", "padUsage");
      exit(1);
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
        if (a == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
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
        if (f == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
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
        if (f == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
        f->initialize(xml);
        m_features.append(f);
      }
      else if (isSubstitutionGroupColorGroup(xml.name())) {
        ColorGroup *c = ColorGroupFactory().create(xml.name());
        if (c == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
        c->initialize(xml);
        m_colorGroups.append(c);
      }
      else if (isSubstitutionGroupLineDescGroup(xml.name())) {
        LineDescGroup *l = LineDescGroupFactory().create(xml.name());
        if (l == NULL) {
          errorInvalidAttribute(xml.name().toString(), "");
          exit(1);
        }
        l->initialize(xml);
        m_lineDescGroups.append(l);
      }
    }
    else if (isEndElementWithName(xml, "Set")) { // </Set>
      return;
    }
  }
}
