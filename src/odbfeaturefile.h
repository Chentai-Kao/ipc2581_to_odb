#ifndef __ODBFEATUREFILE_H__
#define __ODBFEATUREFILE_H__

#include <QtCore>

/* Contains the 4 sections in ODB++ feature file. */
class OdbFeatureFile
{
public:
  QList<QString>& symbolsTable() { return m_symbolsTable; }
  QList<QString>& attributeTable() { return m_attributeTable; }
  QList<QString>& attributeTexts() { return m_attributeTexts; }
  QList<QString>& featuresList() { return m_featuresList; }

private:
  QList<QString> m_symbolsTable;
  QList<QString> m_attributeTable;
  QList<QString> m_attributeTexts;
  QList<QString> m_featuresList;
};

#endif
