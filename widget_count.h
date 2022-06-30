#ifndef WIDGET_COUNT_H
#define WIDGET_COUNT_H

#include <QWidget>
#include <QStackedWidget>
#include <QTableView>
#include <QScrollArea>
#include <QStandardItemModel>
#include <QPlainTextEdit>
#include <QMutex>
#include <QTimer>
#include <QTime>
#include <QFile>
#include "widget_Report.h"
#include "stateTool.h"
#include "countset.h"
#include <windows.h>
#include <tlhelp32.h>
#include <comdef.h>
class Widget_Count : public QWidget
{
	Q_OBJECT

public:
	Widget_Count(QWidget *parent = 0);
	~Widget_Count();
public:
	bool leaveWidget();
	void upDateListInfo();
	void openInNotePad(QString str);
	void ClearAllData(int temp = 0);
	DWORD GetProcessIdFromName(const char*processName)   ;
	void SaveToDatabase();
	bool ChangeQString(QString&);
	void SaveDataToharddisk();
public slots:
	bool slots_intoWidget();
	bool slots_SaveCountInfo();
private slots:
	void slots_timerClearCountInfo();
	void slots_OpenRecord();
	void slots_DeleteRecord();
	void slots_saveRecordOK();
	void slots_saveRecordCancel();
	void slots_shiftOK();
	void slots_shiftCancel();
public:
	CountSet *widgetCountSet;
	QStackedWidget *pStackedCount;
	TemporaryData m_TemporaryData; //手动执行计数清零，保存临时数据
	TemporaryData m_LastData;
	int m_lasterrorData[40][50];
private:
	QWidget *recordWidget;
	QScrollArea *scrollArea;
	WidgetReport * m_WidgetReport;				//饼图报表
	QStandardItemModel *m_modelCount;			//错误数据模板
public:
	QTimer *timerSaveHourList;
	bool bSaveRecord;
	bool bAutoSetZero;
	QTime shift1;
	QTime shift2;
	QTime shift3;

	bool isClear1;
	bool isClear2;
	bool isClear3;
private:
//	Ui::Widget_Count ui;
	void init();
	void initLastData();
};

#endif // WIDGET_COUNT_H
