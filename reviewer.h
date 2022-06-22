#ifndef REVIEWER_H
#define REVIEWER_H

#include <QMainWindow>
#include "ui_reviewer.h"
#include "configinfo.h"
#include "detectThread.h"
#include <QStackedWidget>
#include "widget_title.h"
#include "Widget_CarveSetting.h"
#include "widget_count.h"
class Reviewer : public QMainWindow
{
	Q_OBJECT

public:
	Reviewer(QWidget *parent = 0);
	~Reviewer();
public:
	void initInterface();
	void initLastData();
	void keyPressEvent(QKeyEvent *event);
	bool RoAngle(uchar* pRes,uchar* pTar,int iResWidth,int iResHeight,int iAngle);
	void CarveImage(uchar* pRes,uchar* pTar,int iResWidth,int iResHeight,int iTarX,int iTarY,int iTarWidth,int iTarHeight);
	void GrabCallBack(const s_GBSIGNALINFO *SigInfo);
	void InitImage();
	void ReadCorveConfig();
	void ShowCheckSet(int nCamIdx = 0,int signalNumber = 0);
	void SetCarvedCamInfo();
	void InitCheckSet();
	void InitGrabCard(s_GBINITSTRUCT struGrabCardPara,int index);
	void slots_load();
	void SaveLastData();
public slots:
	void slots_turnPage(int current_page, int iPara = 0);
	void closeEvent(QCloseEvent *e);
	void slots_OnBtnStar();
	void slots_Clear();
public:
	QStackedWidget *statked_widget;
	WidgetTitle *title_widget;
	WidgetCarveSetting *widget_carveSetting;
	Widget_Count *Count_widget;
	QWidget *widget_alg;
	QWidget *stateBar;
	QLabel *labelCoder;
public:
	CMyQueue nQueue[CAMERA_MAX_COUNT];
	DetectThread *pdetthread[CAMERA_MAX_COUNT];
	s_ConfigInfo m_sConfigInfo;
	s_SystemInfo m_sSystemInfo;
	s_ErrorInfo m_sErrorInfo;
	s_RunningInfo m_sRunningInfo;
	CMyErrorList m_ErrorList;
	CCombineRlt m_cCombine;
	CLogFile Logfile;
	QVector<QRgb> m_vcolorTable;
	QMutex m_mutexmCarve[CAMERA_MAX_COUNT];
	TemporaryData LastTimeData;
	QDateTime LastTime;
private:
	Ui::ReviewerClass ui;
public:
	BOOL m_bIsThreadDead;
	CBottleModel m_cBottleModel;
	s_InputCheckerAry CherkerAry;
	s_GBINITSTRUCT struGrabCardPara[CAMERA_MAX_COUNT];
	HANDLE m_pHandles[CAMERA_MAX_COUNT];
	ImageSave m_SavePicture[CAMERA_MAX_COUNT];
	CBottleCheck m_cBottleCheck[CAMERA_MAX_COUNT];
	CBottleCheck m_cBottleRotate[CAMERA_MAX_COUNT];
	CBottleCheck m_cBottleStress[CAMERA_MAX_COUNT];
	s_RealCamInfo m_sRealCamInfo[CAMERA_MAX_COUNT];
	s_CarvedCamInfo m_sCarvedCamInfo[CAMERA_MAX_COUNT];
	CDetectElement m_detectElement[CAMERA_MAX_COUNT];
	QMutex mutexDetectElement[CAMERA_MAX_COUNT];
};

#endif // REVIEWER_H
