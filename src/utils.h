#ifndef __UTILS_H__
#define __UTILS_H__

#include <QtCore>

#define print(t, s) qDebug("%s:%s", (t), (s).toAscii().data())

enum UnitsType {
  MILLIMETER,
  MICRON,
  INCH
};

/* XML element and attribute. */
bool isEndElementWithName(const QXmlStreamReader& xml, const QString& name);
bool isStartElementWithName(const QXmlStreamReader& xml, const QString& name);
const QString getAttributeOrCharacters(QXmlStreamReader& xml,
    const QString elementName, const QString attributeName);
bool hasAttribute(const QXmlStreamReader& xml, const QString attrName);
const QString getAttribute(const QXmlStreamReader& xml, const QString attrName);
void errorInvalidAttribute(
    const QString elementName, const QString attributeName);
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

/* struct used while creating ODB++ features file */
struct OdbFeatureParamLine 
{
  qreal m_xs; // start point
  qreal m_ys;
  qreal m_xe; // end point
  qreal m_ye;
  QString m_symName; // the name in the "feature symbol names" section.
                     // don't store the reference number because it should
                     // be decide by the outer class that uses this struct
  QString m_polarity; // "P" or "N"
};

struct OdbFeatureParamPad 
{
  qreal m_x; // center point
  qreal m_y;
  QString m_symName; // the name in the "feature symbol names" section.
                     // don't store the reference number because it should
                     // be decide by the outer class that uses this struct
  QString m_polarity; // "P" or "N"
  int m_orient; // 0, 1, 2, ..., 7
};

struct OdbFeatureParamArc 
{
  qreal m_xs; // start point
  qreal m_ys;
  qreal m_xe; // end point
  qreal m_ye;
  qreal m_xc; // center point
  qreal m_yc;
  QString m_symName; // the name in the "feature symbol names" section.
                     // don't store the reference number because it should
                     // be decide by the outer class that uses this struct
  QString m_polarity; // "P" or "N"
  QString m_cw; // "Y" for clockwise, "N" for counter clockwise
};

struct OdbFeatureParamText 
{
  // TODO skipped
};

struct OdbFeatureParamBarcode 
{
  // TODO skipped
};

struct OdbFeatureParamSurface 
{
  QString m_polarity; // "P" or "N"
  qreal m_xbs; // polygon start point
  qreal m_ybs;
  QString m_polyType; // "I" for island, "H" for hole
};

struct OdbFeaturePolygonStep
{
  enum StepType { SEGMENT, CURVE } m_type;
  // for both segment (x,y) and curve (xe,ye)
  qreal m_x; // end point
  qreal m_y;
  // for curve only
  qreal m_xc; // curve center point
  qreal m_yc;
  QString m_cw; // "Y" for clockwise, "N" for counter clockwise
};

struct OdbFeatureRecord
{
  // <type> (add REF here denote it is a reference to other feature)
  enum FeatureType { LINE, PAD, ARC, TEXT, BARCODE, SURFACE, REF } m_type;
  // <params>
  OdbFeatureParamLine    *m_paramLine;
  OdbFeatureParamPad     *m_paramPad;
  OdbFeatureParamArc     *m_paramArc;
  OdbFeatureParamText    *m_paramText;
  OdbFeatureParamBarcode *m_paramBarcode;
  OdbFeatureParamSurface *m_paramSurface;
  // <atr, value>
  QHash<QString, QString> m_attribute;
  // (Surface only) polygon segments or curves
  QList<OdbFeaturePolygonStep> m_polygonSteps;
};

#endif
