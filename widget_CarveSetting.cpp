#include "Widget_CarveSetting.h"
#include <QScrollArea>
#include "reviewer.h"
extern Reviewer *pMainFrm;

WidgetCarveSetting::WidgetCarveSetting(QWidget *parent)
	: QWidget(parent)
{
	image_widget = new ImageWidget(this);
	errorList_widget = new CErrorImageList(this);

	listWidget = new QWidget(this);
	QScrollArea *scrollArea = new QScrollArea(listWidget);
	QVBoxLayout* vLayout1 = new QVBoxLayout(listWidget);
	vLayout1->addWidget(scrollArea);
	vLayout1->setSpacing(0);
	vLayout1->setContentsMargins(0,0,0,0);
	QVBoxLayout* vLayout2 = new QVBoxLayout(scrollArea);
	vLayout2->addWidget(errorList_widget);
	vLayout2->setSpacing(0);
	vLayout2->setContentsMargins(5,5,5,5);	
	
	splitter = new QSplitter;
	splitter->addWidget(image_widget);
	splitter->addWidget(listWidget);
	main_layout = new QHBoxLayout();
	main_layout->addWidget(splitter);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(main_layout); 

	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	int width = screenRect.width();

 	listSplitter.append((width-300));
 	listSplitter.append(300);
  	splitter->setSizes(listSplitter);
	iCameraNo = 0;
	connect(errorList_widget,SIGNAL(signals_showErrorImage(QImage*, int, int, double, int, int, QList<QRect>, int )),image_widget, SLOT(slots_showErrorImage(QImage*, int, int, double, int, int, QList<QRect>, int)));
}

WidgetCarveSetting::~WidgetCarveSetting()
{
	
}
