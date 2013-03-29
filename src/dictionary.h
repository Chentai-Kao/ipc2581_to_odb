#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <QtCore>
#include "standardprimitive.h"
#include "userprimitive.h"
#include "linedesc.h"

/* Collect all dictionary, so reference can be easier.
 * e.g. StandardPrimitiveRef, UserPrimitiveRef, LineDescRef ...
 */
class Dictionary
{
public:
  void setEntryStandards(QHash<QString, StandardPrimitive*> d) {
    m_entryStandards = d;
  }
  void setEntryUsers(QHash<QString, UserPrimitive*> d) {
    m_entryUsers = d;
  }
  void setEntryLineDescs(QHash<QString, LineDesc> d) {
    m_entryLineDescs = d;
  }
  const QHash<QString, StandardPrimitive*>& entryStandards() const {
    return m_entryStandards;
  }
  const QHash<QString, UserPrimitive*>& entryUsers() const {
    return m_entryUsers;
  }
  const QHash<QString, LineDesc>& entryLineDescs() const {
    return m_entryLineDescs;
  }
  
private:
  QHash<QString, StandardPrimitive*> m_entryStandards;
  QHash<QString, UserPrimitive*>     m_entryUsers;
  QHash<QString, LineDesc>           m_entryLineDescs;
};

#endif
