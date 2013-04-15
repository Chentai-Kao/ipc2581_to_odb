#ifndef __LENGTH_H__
#define __LENGTH_H__

#include <QtCore>
#include "utils.h"

/* The way to store length while keeping both number and unit */
class Length
{
public:
  Length() {}
  Length(const Length& l) : m_length(l.length()), m_unit(l.unit()) {}
  Length(qreal l, UnitsType u) : m_length(l), m_unit(u) {}

  // getter
  qreal length() const { return m_length; }
  qreal inch() const { return toInch(m_length, m_unit); } // in Inch
  qreal mil() const { return toMil(m_length, m_unit); } // in Mil
  UnitsType unit() const { return m_unit; }

  // operator
  Length operator - (Length& l) {
    if (unit() == l.unit()) {
      return Length(length() - l.length(), unit());
    }
    else {
      return Length(mil() - l.mil(), MIL);
    }
  }

private:
  qreal m_length;
  UnitsType m_unit;
};

#endif
