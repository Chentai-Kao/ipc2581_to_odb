#ifndef __UTILS_H__
#define __UTILS_H__

#include <QtCore>
#include "xform.h"

#define print(t, s) qDebug("%s:%s", (t), (s).toAscii().data())
#define SQR(x) ((x)*(x)) // square of a number
#define ABS(x) ((x) < 0? -(x) : (x))

enum UnitsType {
  MILLIMETER,
  MICRON,
  INCH,
  MIL // for ODB++, a thousandth of inch
};

enum PolygonType {
  POLYGON,
  CUTOUT
};

enum Shape
{
  ROUND,
  SQUARE,
  HEXAGON,
  OCTAGON
};

enum CompLayerSide {
  COMP_TOP,
  COMP_BOT
};

struct PolygonEdge
{
  QPointF m_startPoint;
  QPointF m_endPoint;
  QPointF m_centerPoint;
  bool m_clockwise;
  QString m_odbType; // "OS" for segment, or "OC" for curve
};

/* XML element and attribute. */
bool isEndElementWithName(const QXmlStreamReader& xml, const QString& name);
bool isStartElementWithName(const QXmlStreamReader& xml, const QString& name);
const QString getAttributeOrCharacters(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
bool hasAttribute(const QXmlStreamReader& xml, const QString attrName);
const QString getAttribute(const QXmlStreamReader& xml, const QString attrName);
qreal getNonNegativeDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
qreal getDoubleAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
int getNonNegativeIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
int getIntAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
bool getBoolAttribute(QXmlStreamReader& xml, const QString attributeName);
UnitsType getUnitAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
QString getStringAttribute(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
qreal toInch(qreal num, UnitsType currentUnits);
qreal toMil(qreal num, UnitsType currentUnits);

/* Check for substitution groups. */
bool isSubstitutionGroupAttribute(QStringRef elementName);
bool isSubstitutionGroupColorGroup(QStringRef elementName);
bool isSubstitutionGroupFeature(QStringRef elementName);
bool isSubstitutionGroupFiducial(QStringRef elementName);
bool isSubstitutionGroupLineDescGroup(QStringRef elementName);
bool isSubstitutionGroupPolyStep(QStringRef elementName);
bool isSubstitutionGroupSimple(QStringRef elementName);
bool isSubstitutionGroupStandardPrimitive(QStringRef elementName);
bool isSubstitutionGroupStandardShape(QStringRef elementName);
bool isSubstitutionGroupUserPrimitive(QStringRef elementName);
bool isSubstitutionGroupUserShape(QStringRef elementName);

/* for ODB++ feature */
QPointF calcTransformedLocation(QPointF location, Xform *xform);
int odbDecideOrient(Xform *xform); // 0 (0 degrees, no mirror), 1 (90 degrees...
int odbInsertSymbol(const QString symbol, QList<QString>& symbolsTable);
QString odbRotationSuffix(Xform *xform);
QPointF applyXform(Xform *xform, QPointF src);
QString saveQreal(qreal num); // avoid scientific notation, e.g. 0.00002

/* Some math functions */
qreal calcCorrectAngle(QPointF p0, QPointF p1); // (0~2pi) direction: p0->p1
QPointF rotatePoint(QPointF point, qreal degree);// angle>0 => counter-clockwise
qreal equalAngle(qreal angle); // return the equal angle in [0, 360)

#endif
