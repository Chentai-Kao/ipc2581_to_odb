#ifndef __ERROR_H__
#define __ERROR_H__

#include <QtCore>

class Error
{
public:
  virtual void info() = 0;
};

class InvalidAttributeError : public Error
{
public:
  InvalidAttributeError(QString e, QString a) : m_element(e), m_attribute(a) {}
  virtual void info() {
    qDebug() << QString("ERROR** invalid attribute \"%1\" in <%2>")
                   .arg(m_element).arg(m_attribute);
  }
private:
  QString m_element; // element name
  QString m_attribute; // attribute name
};

class DuplicateIdError : public Error
{
public:
  DuplicateIdError(QString e, QString id) : m_element(e), m_id(id) {}
  virtual void info() {
    qDebug() << QString("ERROR** duplicate id \"%1\" in <%2>")
                   .arg(m_id).arg(m_element);
  }
private:
  QString m_element; // element name
  QString m_id; // id
};

class InvalidElementError : public Error
{
public:
  InvalidElementError(QString e) : m_element(e) {}
  InvalidElementError(QStringRef e) : m_element(e.toString()) {}
  virtual void info() {
    qDebug() << QString("ERROR** Invalid element \"%1\"").arg(m_element);
  }
private:
  QString m_element; // element name
};

class InvalidFileError : public Error
{
public:
  InvalidFileError(QString n) : m_fileName(n) {}
  virtual void info() {
    qDebug() << QString("ERROR** Invalid file \"%1\"").arg(m_fileName);
  }
private:
  QString m_fileName; // file name
};

class NameStartWithDotError : public Error
{
public:
  NameStartWithDotError(QString n) : m_name(n) {}
  virtual void info() {
    qDebug() << QString("ERROR** Name \"%1\" cannot start with dot")
                        .arg(m_name);
  }
private:
  QString m_name; // name
};

class NonImplementedError : public Error
{
public:
  NonImplementedError(QString n) : m_name(n) {}
  virtual void info() {
    qDebug() << QString("ERROR** \"%1\" is not implemented").arg(m_name);
  }
private:
  QString m_name; // the thing that is not implemented
};

#endif
