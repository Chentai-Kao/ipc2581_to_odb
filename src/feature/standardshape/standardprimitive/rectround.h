#ifndef __RECTROUND_H__
#define __RECTROUND_H__

#include "standardprimitive.h"

class RectRound : public StandardPrimitive
{
public:
  virtual void initialize(QXmlStreamReader& xml);
  virtual void odbOutputLayerFeature(
      QList<QString>& symbolsTable,
      QList<QString>& attributeTable,
      QList<QString>& attributeTexts,
      QList<QString>& featuresList,
      QString polarity,
      QPointF location, Xform *xform);

private:
  qreal m_width;
  qreal m_height;
  qreal m_radius;
  bool  m_upperRight;
  bool  m_upperLeft;
  bool  m_lowerLeft;
  bool  m_lowerRight;
};

#endif
