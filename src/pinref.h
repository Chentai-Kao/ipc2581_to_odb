#ifndef __PINREF_H__
#define __PINREF_H__

#include <QtCore>

class PinRef
{
public:
  void initialize(QXmlStreamReader& xml);

private:
  QString m_componentRef;
  QString m_pin;
  QString *m_title;
};

#endif
