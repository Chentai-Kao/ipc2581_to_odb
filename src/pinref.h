#ifndef __PINREF_H__
#define __PINREF_H__

#include <QtCore>

class PinRef
{
public:
  void initialize(QXmlStreamReader& xml);

  // getter
  QString componentRef() { return m_componentRef; }

private:
  // attribute "component" is required in:
  // 1. <Ecad>-<CadData>-<Step>-<PadStack>-<LayerPad>-<PinRef>
  // 2. <Ecad>-<CadData>-<Step>-<LogicalNet>-<PinRef>
  // 3. <Ecad>-<CadData>-<Step>-<LayerFeature>-<Pad>-<PinRef>
  // but may be optional in: (see test cases)
  // 1. <Ecad>-<CadData>-<Step>-<Package>-<LandPattern>-<Pad>-<PinRef>
  QString m_componentRef;
  QString m_pin;
  QString *m_title;
};

#endif
