#include "utils.h"
#include "error.h"

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
    throw new InvalidAttributeError(elementName, attributeName);
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

qreal getNonNegativeDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  qreal value = getDoubleAttribute(xml, elementName, attributeName);
  if (value < 0) {
    throw new InvalidAttributeError(elementName, attributeName);
  }
  return value;
}

qreal getDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  bool ok;
  qreal value = getAttribute(xml, attributeName).toDouble(&ok);
  if (!ok) {
    throw new InvalidAttributeError(elementName, attributeName);
  }
  return value;
}

int getNonNegativeIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  int value = getIntAttribute(xml, elementName, attributeName);
  if (value < 0) {
    throw new InvalidAttributeError(elementName, attributeName);
  }
  return value;
}

int getIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  bool ok;
  int value = getAttribute(xml, attributeName).toInt(&ok);
  if (!ok) {
    throw new InvalidAttributeError(elementName, attributeName);
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
  throw new InvalidAttributeError(elementName, attributeName);
}

QString getStringAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName)
{
  // Note: here doesn't treat empty string "" as error,
  // because in some test cases there are empty strings...don't know why
  return getAttribute(xml, attributeName);
}

bool isSubstitutionGroupAttribute(QStringRef elementName)
{
  return (elementName == "BooleanAttribute" ||
          elementName == "DoubleAttribute" ||
          elementName == "IntegerAttribute" ||
          elementName == "NonstandardAttribute" ||
          elementName == "OptionAttribute" ||
          elementName == "TextAttribute");
}

bool isSubstitutionGroupColorGroup(QStringRef elementName)
{
  return (elementName == "Color" ||
          elementName == "ColorRef");
}

bool isSubstitutionGroupFeature(QStringRef elementName)
{
  return (isSubstitutionGroupStandardShape(elementName) ||
          isSubstitutionGroupUserShape(elementName));
}

bool isSubstitutionGroupFiducial(QStringRef elementName)
{
  return (elementName == "BadBoardMark" ||
          elementName == "GlobalFiducial" ||
          elementName == "GoodPanelMark" ||
          elementName == "LocalFiducial");
}

bool isSubstitutionGroupLineDescGroup(QStringRef elementName)
{
  return (elementName == "LineDesc" ||
          elementName == "LineDescRef");
}

bool isSubstitutionGroupPolyStep(QStringRef elementName)
{
  return (elementName == "PolyStepCurve" ||
          elementName == "PolyStepSegment");
}

bool isSubstitutionGroupSimple(QStringRef elementName)
{
  return (elementName == "Arc" ||
          elementName == "Line" ||
          elementName == "Outline" ||
          elementName == "Polyline");
}

bool isSubstitutionGroupStandardPrimitive(QStringRef elementName)
{
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

bool isSubstitutionGroupStandardShape(QStringRef elementName)
{
  return (isSubstitutionGroupStandardPrimitive(elementName) ||
          elementName == "StandardPrimitiveRef");
}

bool isSubstitutionGroupUserPrimitive(QStringRef elementName)
{
  return (isSubstitutionGroupSimple(elementName) ||
          elementName == "Text" ||
          elementName == "UserSpecial");
}

bool isSubstitutionGroupUserShape(QStringRef elementName)
{
  return (isSubstitutionGroupUserPrimitive(elementName) ||
          elementName == "UserPrimitiveRef");
}

QPointF odbDecideTransformedLocation(QPointF location, Xform *xform)
{
  if (xform == NULL) {
    return location;
  }
  return QPointF(location.x() + xform->offset().x() * xform->scale(),
                 location.y() + xform->offset().y() * xform->scale());
}

int odbDecideOrient(Xform *xform)
{
  // 0 : 0 degrees, no mirror
  // 1 : 90 degrees, no mirror
  // 2 : 180 degrees, no mirror
  // 3 : 270 degrees, no mirror
  // 4 : 0 degrees, mirror in X axis
  // 5 : 90 degrees, mirror in X axis
  // 6 : 180 degrees, mirror in X axis
  // 7 : 270 degrees, mirror in X axis
  if (xform == NULL) {
    return 0;
  }

  qreal degree = xform->rotation();
  bool mirror = xform->mirror();
  if (!mirror) {
    if (degree < 45 || degree >= 315) {
      return 0;
    }
    else if (degree < 135) {
      return 1;
    }
    else if (degree < 225) {
      return 2;
    }
    else if (degree < 315) {
      return 3;
    }
  }
  else {
    if (degree < 45 || degree >= 315) {
      return 4;
    }
    else if (degree < 135) {
      return 5;
    }
    else if (degree < 225) {
      return 6;
    }
    else if (degree < 315) {
      return 7;
    }
  }
}

int odbInsertSymbol(const QString symbol, QList<QString>& symbolsTable)
{
  // insert symbol if necessary, return its final index
  int symNum = symbolsTable.indexOf(symbol);
  if (symNum == -1) {
    symNum = symbolsTable.size();
    symbolsTable.append(symbol);
  }
  return symNum;
}

qreal calcCorrectAngle(QPointF p0, QPointF p1)
{
  QPointF v = p1 - p0;
  qreal arcTan = qAtan(v.y() / v.x());
  if (v.x() < 0) {
    return arcTan + M_PI;
  }
  else if (v.y() < 0) {
    return arcTan + 2 * M_PI;
  }
  return arcTan;
}
