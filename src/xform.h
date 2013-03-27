#ifndef __XFORM_H__
#define __XFORM_H__

#include <QtCore>

class Xform
{
public:
  void initialize(QXmlStreamReader& xml);
  
  // getter
  QPointF offset() { return m_offset; }
  qreal rotation() { return m_rotation; }
  bool mirror() { return m_mirror; }
  qreal scale() { return m_scale; }

private:
  QPointF m_offset;
  qreal m_rotation;
  bool m_mirror;
  qreal m_scale;
};

#endif
