#ifndef DETECTTHREAD_H
#define DETECTTHREAD_H

#include <QThread>
#include "stateTool.h"
#pragma once 
class DetectThread : public QThread
{
	Q_OBJECT

public:
	DetectThread(QObject *parent,int);
	~DetectThread();
public:
	void run();
	void ProcessHanlde(int);
signals:
	void signals_updateActiveImg(int nCamNo,int nImgNo,double dCostTime,int tmpResult);
	void signals_AddErrorTableView(int nCamSN,int nSignalNo,int nErrorType);
	void signals_upDateCamera(int nCam,int nMode = 0);
	void signals_updateCameraFailureRate();
	void signals_updateImage(QImage*, QString, QString, QString, QString, QString, QList<QRect> ,int );
private:
	void DetectNormal(CGrabElement *pElement,int pLocation);
	void rotateImage(CGrabElement *pElement);
	void checkImage(CGrabElement *pElement,int iCheckMode);
	bool getCheckResult(CGrabElement *pElement);
	void CountDefectIOCard(int nSignalNo,int tmpResult);
	void saveImage(CGrabElement *pElement);
	void addErrorImageList(CGrabElement *pElement);
	void upDateState(QImage *pElement, int signalNo,double costTime, int nMouldID, QList<QRect>, int);
	//��ȡ���ģ���������
	void GetModelDotData(CGrabElement *pElement);
private:
	bool m_bStopThread;					//�������
	int m_threadId;
	bool bCheckResult[CAMERA_MAX_COUNT];
	int iErrorType;
	int iMaxErrorType;
	int iMaxErrorArea;
	CSpendTime checkTimecost;
	QDir *dirSaveImagePath;
	//�����㷨
	s_AlgCInP sAlgCInp;						//����������
	s_AlgCheckResult *pAlgCheckResult;		//���ؼ�����ṹ��
	s_Status  sReturnStatus;				// ����ִ��״̬��Ϣ
	s_Loc_Ori tempOri;
public:
	int iCamera;
	int iImageNo;
};

#endif
