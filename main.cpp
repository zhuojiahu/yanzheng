#include "reviewer.h"
#include <QApplication>
#include <QTranslator>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTranslator translator;
	translator.load(".\\Reviewer_zh.qm");
	a.installTranslator(&translator);
	//QFile qss(".\\GlasswareDetect.qss");
	//qss.open(QFile::ReadOnly);
	//qApp->setStyleSheet(qss.readAll());
	//qss.close();
	Reviewer w;
	w.show();
	return a.exec();
}
