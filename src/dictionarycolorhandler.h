#ifndef __DICTIONARYCOLORHANDLER_H__
#define __DICTIONARYCOLORHANDLER_H__

#include <QtCore>
#include "handler.h"
#include "color.h"

class DictionaryColorHandler : public Handler
{
public:
  virtual void run(QXmlStreamReader& xml);

private:
  QHash<QString, Color> m_colors; // (id,EntryColor)
};

#endif
