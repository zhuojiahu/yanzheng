#include "myimageshowitem.h"
#include <QLabel>
#include <QLayout>
#include <QDateTime>
#include <QFileDialog>
#include "reviewer.h"
extern Reviewer *pMainFrm;

MyImageShowItem::MyImageShowItem(QWidget *parent)
	: QWidget(parent)
{
	bIsUpdateImage = true;
	bIsMaxShow = false;
	bIsCheck = true;
	colorRect = QColor(0,0,0);
	createActions();

	m_vcolorTable.clear();
	for (int i = 0; i < 256; i++)  
	{  
		m_vcolorTable.append(qRgb(i, i, i)); 
	}
}

MyImageShowItem::~MyImageShowItem()
{
	contextMenu->clear(); //清除菜单
	delete contextMenu;
}
void MyImageShowItem::createActions()
{
	contextMenu = new QMenu();
	saveAction = new QAction(tr("Save image"),this);
	connect(saveAction,SIGNAL(triggered()),this,SLOT(slots_saveImage()));
	stopCheck =  new QAction(tr("Stop check"),this);
	connect(stopCheck,SIGNAL(triggered()),this,SLOT(slots_stopCheck()));
	stopAllStressCheck =  new QAction(tr("Stop All Stress check"),this);
	connect(stopAllStressCheck,SIGNAL(triggered()),this,SLOT(slots_stopAllStressCheck()));
	startCheck =  new QAction(tr("Start check"),this);
	connect(startCheck,SIGNAL(triggered()),this,SLOT(slots_startCheck()));
	startAllStressCheck =  new QAction(tr("Start All Stress check"),this);
	connect(startAllStressCheck,SIGNAL(triggered()),this,SLOT(slots_startAllStressCheck()));
	startFreshAll = new QAction(tr("Start Refresh All Camera"),this);
	connect(startFreshAll,SIGNAL(triggered()),this,SLOT(slots_startShowAll()));
	showCheck = new QAction(tr("Set algorithm"),this);
	connect(showCheck,SIGNAL(triggered()),this,SLOT(slots_showCheck()));
}

void MyImageShowItem::inital(int nCamNo)
{
	iCameraNo = nCamNo;
	strCamera = "null";
	strImageSN = "null";
	strTime = "null";
	strResult = "null";
	update();
}
void MyImageShowItem::paintEvent(QPaintEvent *event)
{
	//添加边框
	if (!pMainFrm->m_sSystemInfo.m_iImageStretch && !bIsMaxShow)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(1, 1, this->width()-2*1, this->height()-2*1);

		QPainter painterRect(this);
		painterRect.setRenderHint(QPainter::Antialiasing, true);//消除锯齿
		painterRect.fillPath(path, QBrush(Qt::white));

		QColor color(0, 0, 0);
		painterRect.setPen(color);
		painterRect.drawPath(path);
	}

	if (imageForWidget.isNull())
	{
		return;
	}
	int widgetWidth = geometry().width()-4;
	int widgetHeight = geometry().height()-4;
	int iShowWidth = widgetWidth;
	int iShowHeight = widgetHeight;
	int iShowX = 0;
	int iShowY = 0;
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::red);
// 	painter.drawPixmap(QRect(0, 0, widgetWidth, widgetHeight),pixmapShown);
	if (bIsMaxShow)
	{
		int imgwidth = imageForWidget.width();
		int imgheight = imageForWidget.height();
		if (1.0*widgetWidth/widgetHeight > 1.0*imgwidth/imgheight)
		{
			iShowWidth = 1.0*imageForWidget.width()/imageForWidget.height()*widgetHeight;
			iShowHeight = widgetHeight;
			iShowX = (widgetWidth-iShowWidth)/2;
			iShowY = 0;
			painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
		}
		else
		{
			iShowWidth = widgetWidth;
			iShowHeight = 1.0*imageForWidget.height()/imageForWidget.width()*widgetWidth;
			iShowX = 0;
			iShowY = (widgetHeight-iShowHeight)/2;
			painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
		}
	}
	else
	{
		if (pMainFrm->m_sSystemInfo.m_iImageStretch)
		{
			iShowWidth = widgetWidth;
			iShowHeight = widgetHeight;
			iShowX = 0;
			iShowY = 0;
			painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
		}
		else
		{
			int imgwidth = imageForWidget.width();
			int imgheight = imageForWidget.height();

			if (1.0*widgetWidth/widgetHeight > 1.0*imgwidth/imgheight)
			{
				iShowWidth = 1.0*imageForWidget.width()/imageForWidget.height()*widgetHeight;
				iShowHeight = widgetHeight;
				iShowX = (widgetWidth-iShowWidth)/2 + 2;
				iShowY = 0 + 2;
				painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
			}
			else
			{
				iShowWidth = widgetWidth;
				iShowHeight = 1.0*imageForWidget.height()/imageForWidget.width()*widgetWidth;
				iShowX = 0 + 2;
				iShowY = (widgetHeight-iShowHeight)/2 + 2;
				painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
			}
		}
	}
	
	QFont font("宋体",9,QFont::DemiBold,false);
	QPen pen(Qt::blue);
	pen.setWidth(2);
	painter.setFont(font);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);
//	painter.drawText(0, 20, tr("Camera:")+QString::number(iCameraNo));
	painter.drawText(0, 20, tr("Camera:")+strCamera);
	painter.drawText(0, 40, tr("ImageSN:")+strImageSN);
	painter.drawText(0, 60, tr("CostTime:")+strTime);
	if (listErrorRect.length()>0)
	{
		pen.setColor(Qt::red);
		painter.setPen(pen);
	}
	painter.drawText(0, 80, tr("Result:")+strResult);
	
	//淡蓝画笔
	pen.setColor(Qt::magenta);
	pen.setWidth(3);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);

	//输出警报信息
	if (bIsHaveWarning)
	{
		painter.drawText(0,  geometry().height()/2, geometry().width(), geometry().height()/2, Qt::AlignCenter|Qt::TextWordWrap, strWarning);
	}

	//输出状态信息
	if (!bIsCheck)
	{
		painter.drawText(0, 0, geometry().width(), 20, Qt::AlignRight, tr("Check Stoped"));
	}
	if (!bIsUpdateImage)
	{
		painter.drawText(0, 20, geometry().width(), 20, Qt::AlignRight, tr("Refresh Stoped"));
	}
	//红色画笔
	QFont font2("Arial",16,QFont::Bold);
	pen.setColor(Qt::red);
	pen.setWidth(3);
	painter.setFont(font2);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);
	//画矩形框
	double scaleWidth = 1.0*iShowWidth/iImageWidth;
	double scaleHeight = 1.0*iShowHeight/iImageHeight;

	for (int i = 0; i<listErrorRect.length(); i++)
	{
		QRect rect = listErrorRect.at(i);
		painter.drawRect(rect.left() * scaleWidth+iShowX, rect.top() * scaleHeight+iShowY, rect.width() * scaleWidth, rect.height() * scaleHeight);
	}

	//输出错误信息
	if (bIsHaveError)
	{
		painter.drawText(0, 0, geometry().width(), geometry().height(), Qt::AlignCenter|Qt::TextWordWrap, strError);
	}
}


void MyImageShowItem::mouseDoubleClickEvent(QMouseEvent *event)
{	
	emit signals_imageItemDoubleClick(iCameraNo);
}
void MyImageShowItem::contextMenuEvent(QContextMenuEvent *event)
{
	contextMenu->clear(); //清除原有菜单
	QPoint point = event->pos(); //得到窗口坐标
	contextMenu->addAction(saveAction);
	if (bIsCheck)
	{
		contextMenu->addAction(stopCheck);
	}
	else
	{
		contextMenu->addAction(startCheck);
	}
	if (!pMainFrm->widget_carveSetting->image_widget->bIsStopAllStessCheck)
	{
		contextMenu->addAction(stopAllStressCheck);
	}
	else
	{
		contextMenu->addAction(startAllStressCheck);
	}
	contextMenu->addAction(startFreshAll);
	contextMenu->addAction(showCheck);
	//菜单出现的位置为当前鼠标的位置
	contextMenu->exec(QCursor::pos());
	event->accept();
}
void MyImageShowItem::updateImage(QImage* imageShown,QString camera, QString imageSN,QString time, QString result, QString mouldID, QList<QRect> listRect)
{
	try
	{
		imageForWidget = (imageShown)->mirrored();
	}
	catch (...)
	{
		pMainFrm->Logfile.write(("get picture error"),CheckLog);
		return;
	}

	strCamera = camera;
	strImageSN = imageSN;
	strTime = time;
	strResult = result;
	strMouldID = mouldID;
	listErrorRect = listRect;
	iImageWidth = imageForWidget.width();
	iImageHeight = imageForWidget.height();
	repaint();

}
void MyImageShowItem::slots_updateImage(QImage* imageShown,QString camera, QString imageSN,QString time, QString result, QString mouldID, QList<QRect> listRect,int ImageCount)
{
	//总共有24个对象，每个对象的标识是icamerano，需要根据camera和ImageCount来确定是哪个icamerano刷新
	if(QString::number(iCameraNo) != camera)
	{
		return;
	}
	if (imageShown == NULL)
	{
		return;
	}
	if (pMainFrm->nQueue[iCameraNo].InitID != ImageCount)
	{
		return;
	}
	if(bIsUpdateImage)
	{
		updateImage(imageShown,QString::number(iCameraNo+1),imageSN,time, result, mouldID, listRect);
	}
}
void MyImageShowItem::slots_update()
{
	update();
}

void MyImageShowItem::slots_saveImage()
{
	QTime time = QTime::currentTime();
	QDate date = QDate::currentDate();
	QString strImgPath = tr("SaveImage/");
	strImgPath = strImgPath+tr("Camera%1/").arg(iCameraNo+1);
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"),\
		".\\SaveImage\\" + QString("%1-%2-%3-%4%5%6.bmp").arg(date.year()).arg(date.month()).arg(date.day()).arg(time.hour()).arg(time.minute()).arg(time.second()),\
		tr("Images (*.bmp *.png *.jpg)"));
	QDir *dir = new QDir;
	QString strFilePath = fileName.left(fileName.findRev("\\")+1);
	if(!dir->exists(strFilePath))
	{
		bool ok = dir->mkpath(strFilePath);
	}
	dir=NULL;
	if (!fileName.isEmpty())
	{
		imageForWidget.save(fileName);
	}

}
void MyImageShowItem::slots_showCheck()
{
	emit signals_showCheck(iCameraNo);
}
void MyImageShowItem::slots_stopCheck()
{
	bIsCheck = false;
	bIsUpdateImage = false;
	emit signals_stopCheck(iCameraNo );
	update();
}
void MyImageShowItem::slots_stopAllStressCheck()
{
	emit signals_stopAllStressCheck();
	update();
}
void MyImageShowItem::slots_startAllStressCheck()
{
	emit signals_stopAllStressCheck();
	update();
}
void MyImageShowItem::slots_startCheck()
{
	bIsCheck = true;
	bIsUpdateImage = true;
	emit signals_startCheck(iCameraNo );
	update();

}
void MyImageShowItem::slots_startShow()
{
	bIsUpdateImage = true;
	update();
}
void MyImageShowItem::slots_stopShow()
{
	bIsUpdateImage = false;
	update();
}
void MyImageShowItem::slots_startShowAll()
{
	emit signals_startShowAll();
	for (int i=0;i<CAMERA_MAX_COUNT;i++)
	{
		pMainFrm->m_SavePicture[i].pThat=NULL;
	}
}
void MyImageShowItem::setMaxShow(bool bSatus)
{
	bIsMaxShow = bSatus;
}
