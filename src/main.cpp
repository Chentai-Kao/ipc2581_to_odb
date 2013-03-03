#include <QtCore>
#include <cstdio>

int main()
{
  /* Open file */
  QFile *file = new QFile("example.xml");
  if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
    fprintf(stderr, "Can't open file\n");
  }
  fprintf(stdout, "File opened!\n");

  /* Read XML */
  QXmlStreamReader xml(file);
  qint32 depth = 0; // keep track of the depth of data
  QString msg;
  while (!xml.atEnd() && !xml.hasError()) {
    QXmlStreamReader::TokenType token = xml.readNext();
    switch (token) {
      case QXmlStreamReader::StartElement:
        qDebug() << msg;
        msg = QString(depth * 2, ' ').append(xml.name());
        ++depth;
        break;
      case QXmlStreamReader::EndElement:
        --depth;
        break;
      case QXmlStreamReader::Characters:
        if (!xml.isWhitespace()) {
          msg.append(": ").append(xml.text());
        }
        break;
      default:
        break;
    }
  }
  fprintf(stdout, "Finished reading!\n");
}
