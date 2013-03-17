#include "utils.h"
#include "settings.h"

bool isEndElementWithName(const QXmlStreamReader& xml, const QString& name)
{
  return (xml.isEndElement() && xml.name() == name);
}

bool isStartElementWithName(const QXmlStreamReader& xml, const QString& name)
{
  return (xml.isStartElement() && xml.name() == name);
}

const QString getAttributeOrCharacters(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  // first search for attribute
  QString value = getAttribute(xml, attributeName);
  // if failed, search for nested text
  if (value == "") {
    value = xml.readElementText();
  }
  // if still failed, it is an error
  if (value == "") {
    errorInvalidAttribute(elementName, attributeName);
    exit(1);
  }
  return value;
}

bool hasAttribute(const QXmlStreamReader& xml, const QString attrName)
{
  return xml.attributes().hasAttribute(attrName);
}

const QString getAttribute(const QXmlStreamReader& xml, const QString attrName)
{
  return xml.attributes().value("", attrName).toString();
}

void createOdbDir(const QString& path)
{
  QDir(OUTPUT_PATH).mkpath(path.toLower());
}

void errorInvalidAttribute(
    const QString elementName, const QString attributeName)
{
  qDebug("ERROR** invalid attribute \"%s\" in <%s>",
      attributeName.toAscii().data(),
      elementName.toAscii().data());
}

qreal getNonNegativeDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  qreal value = getDoubleAttribute(xml, elementName, attributeName);
  if (value < 0) {
    errorInvalidAttribute(elementName, attributeName);
    exit(1);
  }
  return value;
}

qreal getDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  bool ok;
  qreal value = getAttribute(xml, attributeName).toDouble(&ok);
  if (!ok) {
    errorInvalidAttribute(elementName, attributeName);
    exit(1);
  }
  return value;
}

int getNonNegativeIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  int value = getIntAttribute(xml, elementName, attributeName);
  if (value < 0) {
    errorInvalidAttribute(elementName, attributeName);
    exit(1);
  }
  return value;
}

int getIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  bool ok;
  int value = getAttribute(xml, attributeName).toInt(&ok);
  if (!ok) {
    errorInvalidAttribute(elementName, attributeName);
    exit(1);
  }
  return value;
}

bool getBoolAttribute(QXmlStreamReader& xml, const QString attributeName)
{
  return (getAttribute(xml, attributeName) == "TRUE");
}

UnitsType getUnitAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  QString units = getAttribute(xml, attributeName);
  if (units == "MILLIMETER") {
    return MILLIMETER;
  }
  else if (units == "MICRON") {
    return MICRON;
  }
  else if (units == "INCH") {
    return INCH;
  }
  errorInvalidAttribute(elementName, attributeName);
  exit(1);
  return INCH;
}

QString getStringAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  // Note: here doesn't treat empty string "" as error,
  // because in some test cases there are empty strings...don't know why
  return getAttribute(xml, attributeName);
}

bool isSubstitutionGroupAttribute(QStringRef elementName) {
  return (elementName == "BooleanAttribute" ||
          elementName == "DoubleAttribute" ||
          elementName == "IntegerAttribute" ||
          elementName == "NonstandardAttribute" ||
          elementName == "OptionAttribute" ||
          elementName == "TextAttribute");
}

bool isSubstitutionGroupColorGroup(QStringRef elementName) {
  return (elementName == "Color" ||
          elementName == "ColorRef");
}

bool isSubstitutionGroupFeature(QStringRef elementName) {
  return (isSubstitutionGroupStandardShape(elementName) ||
          isSubstitutionGroupUserShape(elementName));
}

bool isSubstitutionGroupFiducial(QStringRef elementName) {
  return (elementName == "BadBoardMark" ||
          elementName == "GlobalFiducial" ||
          elementName == "GoodPanelMark" ||
          elementName == "LocalFiducial");
}

bool isSubstitutionGroupLineDescGroup(QStringRef elementName) {
  return (elementName == "LineDesc" ||
          elementName == "LineDescRef");
}

bool isSubstitutionGroupPolyStep(QStringRef elementName) {
  return (elementName == "PolyStepCurve" ||
          elementName == "PolyStepSegment");
}

bool isSubstitutionGroupSimple(QStringRef elementName) {
  return (elementName == "Arc" ||
          elementName == "Line" ||
          elementName == "Outline" ||
          elementName == "Polyline");
}

bool isSubstitutionGroupStandardPrimitive(QStringRef elementName) {
  return (elementName == "Butterfly" ||
          elementName == "Circle" ||
          elementName == "Contour" ||
          elementName == "Diamond" ||
          elementName == "Donut" ||
          elementName == "Ellipse" ||
          elementName == "Hexagon" ||
          elementName == "Moire" ||
          elementName == "Octagon" ||
          elementName == "Oval" ||
          elementName == "RectCenter" ||
          elementName == "RectCham" ||
          elementName == "RectCorner" ||
          elementName == "RectRound" ||
          elementName == "Thermal" ||
          elementName == "Triangle");
}

bool isSubstitutionGroupStandardShape(QStringRef elementName) {
  return (isSubstitutionGroupStandardPrimitive(elementName) ||
          elementName == "StandardPrimitiveRef");
}

bool isSubstitutionGroupUserPrimitive(QStringRef elementName) {
  return (isSubstitutionGroupSimple(elementName) ||
          elementName == "Text" ||
          elementName == "UserSpecial");
}

bool isSubstitutionGroupUserShape(QStringRef elementName) {
  return (isSubstitutionGroupUserPrimitive(elementName) ||
          elementName == "UserPrimitiveRef");
}

