#ifndef CARVE_SETTING_H
#define CARVE_SETTING_H

#include <QWidget>
#include <QStackedWidget>
#include <QToolButton>
#include <QSplitter>
#include "widget_image.h"
#include "cerrorimagelist.h"

#include "DHBaseWidget.h"

class WidgetCarveSetting : public QWidget
{
	Q_OBJECT

public:
	WidgetCarveSetting(QWidget *parent = 0);
	~WidgetCarveSetting();
public:
	QHBoxLayout *main_layout;
	QSplitter *splitter;
	ImageWidget *image_widget;//����ͼ����ʾ�����е�ͼ�����ģ��
	QWidget *listWidget;
	CErrorImageList *errorList_widget;
	int iCameraNo;
private:
	QList<int> listSplitter;

};

#endif // CARVE_SETTING_H
