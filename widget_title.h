#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "pushButton.h"
#include "toolButton.h"
#include "common.h"

class WidgetTitle : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetTitle(QWidget *parent = 0);
	void addToolName();
	void setState(bool);
	void setState(int pPermission,bool isUnLock);
signals:
	void turnPage(int current_page);
public slots:
	void turnPage(QString current_page);
private:
	QLabel *version_title; //标题
public:
	QList<ToolButton *> button_list;
};

#endif // TITLEWIDGET_H
