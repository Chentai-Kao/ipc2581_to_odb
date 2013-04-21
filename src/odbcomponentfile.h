#ifndef __ODBCOMPONENTFILE_H__
#define __ODBCOMPONENTFILE_H__

#include <QtCore>

/* Contains the 2 sections in ODB++ component file. */
class OdbComponentFile
{
public:
  QList<QString>& attributeTable() { return m_attributeTable; }
  QList<QString>& componentList() { return m_componentList; }

private:
  QList<QString> m_attributeTable;
  QList<QString> m_componentList;
};

#endif
