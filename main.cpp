#include "reviewer.h"
#include <QApplication>
#include <QTranslator>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTranslator translator;
	translator.load(".\\Reviewer_zh.qm");
	a.installTranslator(&translator);
	QApplication::addLibraryPath("./QtPlugins");
	//a.setWindowIcon(QIcon("./Resources/LOGO.png"));
	Reviewer w;
	w.show();
	return a.exec();
}
