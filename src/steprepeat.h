#ifndef __STEP_REPEAT_H__
#define __STEP_REPEAT_H__

#include <QtCore>

class StepRepeat
{
public:
  void initialize(QXmlStreamReader& xml);

  // getter
  QString stepRef() { return m_stepRef; }
  qreal x() { return m_x; }
  qreal y() { return m_y; }
  int nx() { return m_nx; }
  int ny() { return m_ny; }
  qreal dx() { return m_dx; }
  qreal dy() { return m_dy; }
  qreal angle() { return m_angle; }
  bool mirror() { return m_mirror; }

private:
  QString m_stepRef;
  qreal   m_x;
  qreal   m_y;
  int     m_nx;
  int     m_ny;
  qreal   m_dx;
  qreal   m_dy;
  qreal   m_angle;
  bool    m_mirror;
};

#endif
