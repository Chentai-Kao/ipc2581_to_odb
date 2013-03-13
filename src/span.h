#ifndef __SPAN_H__
#define __SPAN_H__

#include <QtCore>

class Span
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_fromLayer;
  QString m_toLayer;
};

#endif
