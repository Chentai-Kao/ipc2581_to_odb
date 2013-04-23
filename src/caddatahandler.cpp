#include "caddatahandler.h"

void
CadDataHandler::run(QXmlStreamReader& xml, UnitsType units)
{
  m_stackup = NULL;
  while (!xml.atEnd() && !xml.hasError()) {
    xml.readNext();
    if (xml.isStartElement()) {
      if (xml.name() == "Layer") {
        Layer layer;
        layer.initialize(xml);
        g_layers.append(layer);
      }
      else if (xml.name() == "Stackup") {
        m_stackup = new Stackup();
        m_stackup->initialize(xml, units);
      }
      else if (xml.name() == "Step") {
        Step step;
        step.initialize(xml, units);
        m_steps.append(step);
      }
    }
    else if (isEndElementWithName(xml, "CadData")) { // </CadData>
      return;
    }
  }
}

void
CadDataHandler::odbOutputMatrixAllLayers(QTextStream& out)
{
  int rowNum = 1;
  // COMPONENT TOP
  odbOutputLayer(
      out, rowNum++, "BOARD", "COMPONENT", COMP_TOP_NAME, "POSITIVE", "", "");
  // SILK_SCREEN TOP
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].type() == "SILK_SCREEN" && g_layers[i].isTop()) {
      odbOutputSingleLayer(out, rowNum++, g_layers[i]);
      break;
    }
  }
  // SOLDER_PASTE TOP
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].type() == "SOLDER_PASTE" && g_layers[i].isTop()) {
      odbOutputSingleLayer(out, rowNum++, g_layers[i]);
      break;
    }
  }
  // SOLDER_MASK TOP
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].type() == "SOLDER_MASK" && g_layers[i].isTop()) {
      odbOutputSingleLayer(out, rowNum++, g_layers[i]);
      break;
    }
  }
  // SIGNAL
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].type() == "SIGNAL" ||
        g_layers[i].type() == "POWER_GROUND" ||
        g_layers[i].type() == "MIXED") {
      odbOutputSingleLayer(out, rowNum++, g_layers[i]);
    }
  }
  // SOLDER_MASK BOTTOM
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].type() == "SOLDER_MASK" && g_layers[i].isBottom()) {
      odbOutputSingleLayer(out, rowNum++, g_layers[i]);
      break;
    }
  }
  // SOLDER_PASTE BOTTOM
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].type() == "SOLDER_PASTE" && g_layers[i].isBottom()) {
      odbOutputSingleLayer(out, rowNum++, g_layers[i]);
      break;
    }
  }
  // SILK_SCREEN BOTTOM
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].type() == "SILK_SCREEN" && g_layers[i].isBottom()) {
      odbOutputSingleLayer(out, rowNum++, g_layers[i]);
      break;
    }
  }
  // ROUT (TODO)
  // COMPONENT BOTTOM
  odbOutputLayer(
      out, rowNum++, "BOARD", "COMPONENT", COMP_BOT_NAME, "POSITIVE", "", "");
  // DRILL
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].type() == "DRILL") {
      odbOutputSingleLayer(out, rowNum++, g_layers[i]);
      break;
    }
  }
  // (MISC) DOCUMENT
  for (int i = 0; i < g_layers.size(); ++i) {
    if (g_layers[i].type() == "DOCUMENT") {
      odbOutputSingleLayer(out, rowNum++, g_layers[i]);
      break;
    }
  }
  // (MISC) SQA_AREAS
  // (MISC) HEIGHT_TOP
}

void
CadDataHandler::odbOutputLayerFeature(
    OdbFeatureFile& file, QString stepName, QString layerName)
{
  // find the step, and let it draw
  for (int i = 0; i < m_steps.size(); ++i) {
    if (m_steps[i].name() == stepName) {
      m_steps[i].odbOutputLayerFeature(file, layerName);
      break;
    }
  }
}

QList<Component>&
CadDataHandler::components(QString stepName)
{
  for (int i = 0; i < m_steps.size(); ++i) {
    if (m_steps[i].name() == stepName) {
      return m_steps[i].components();
    }
  }
  throw new ProgramLogicError("CadDataHandler::components()");
}

void
CadDataHandler::odbOutputLayer(QTextStream& out, int rowNum, QString context,
    QString type, QString name, QString polarity,
    QString startName, QString endName)
{
  out << "LAYER {\n";
  out << QString("   ROW=%1\n").arg(rowNum);
  out << QString("   CONTEXT=%1\n").arg(context);
  out << QString("   TYPE=%1\n").arg(type);
  out << QString("   NAME=%1\n").arg(name);
  out << QString("   OLD_NAME=\n");
  out << QString("   POLARITY=%1\n").arg(polarity);
  out << QString("   START_NAME=%1\n").arg(startName);
  out << QString("   END_NAME=%1\n").arg(endName);
  out << "}\n";
  out << "\n";
}

void
CadDataHandler::odbOutputSingleLayer(QTextStream& out, int rowNum, Layer& layer)
{
  odbOutputLayer(out, rowNum, layer.context(),
      layer.type(), layer.name(), layer.polarity(),
      layer.spanFromLayer(), layer.spanToLayer());
}
