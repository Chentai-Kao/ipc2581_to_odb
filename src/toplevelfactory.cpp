#include "toplevelfactory.h"

Handler*
TopLevelFactory::create(QStringRef elementName)
{
  // choose from <Content> <LogisticHeader> <HistoryRecord> <Bom> <Ecad> <Avl>
  if (elementName == "Content") {
    return new ContentHandler();
  }
  else if (elementName == "LogisticHeader") {
    return new LogisticHeaderHandler();
  }
  else if (elementName == "HistoryRecord") {
    return new HistoryRecordHandler();
  }
  else if (elementName == "Bom") {
    return new BomHandler();
  }
  else if (elementName == "Ecad") {
    return new EcadHandler();
  }
  else if (elementName == "Avl") {
    return new AvlHandler();
  }

  return NULL;
}
