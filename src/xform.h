#ifndef __XFORM_H__
#define __XFORM_H__

#include <QtCore>

class Xform
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QPointF m_offset;
  qreal m_rotation;
  bool m_mirror;
  qreal m_scale;
};

#endif
