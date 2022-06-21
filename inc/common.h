#ifndef COMMON_H
#define COMMON_H
#pragma once

//���_WIN32_WINNT δ����ı��뾯��
#ifndef _WIN32_WINNT 
#define _WIN32_WINNT 0x0502
#endif

#define SHADOW_WIDTH            0
#define IMAGE_SPACE             10
#define TITEL_HEIGHT            110
#define SPPEDHIGHEST            400
#define SPPEDNORMAL             300

#define DEFAULT_SKIN            ":/skin/1b"
#include <qimage.h>
#include <QWaitCondition>
#include <QMutex>
#include "qt_windows.h"

#pragma comment(lib, "version.lib")

#pragma warning(disable:4005) //����ʾ���ض��徯��

//����������
#define CAMERA_MAX_COUNT 40
//���������͸���
#define ERRORTYPE_MAX_COUNT 50
#define IOCard_MAX_COUNT 2
//����ͼ�����
#define ERROR_IMAGE_COUNT 30

#define PASSWORD3 "kongping"

typedef enum{
	UI_EN,
	UI_ZH
}LANGUAGE;

// ����������
enum e_CurrentMainPage	
{
	CarveSettingPage,
	CountPage,
	ManagementSettingPage,
	AlgPage,
	PlcPage
};

enum e_ToolButton	
{
	ImageButton = 0,
	InfoButton,
	CarveSettingButton,
	ManagementSettingButton,
	TestButton,
	CountButton,
	AlgButton
};

//������־����
enum e_SaveLogType	    
{
	OperationLog = 0,			//������־
	DebugLog,					//������־(ȱͼ || �󴥷� || ������Ϊ�� ����־��Ϣ)
	AbnormityLog,               //�쳣��־(�쳣���� || �����ϲ�Ӧ���ֵ��жϴ���)

	CheckLog,		            //�����־
	MendParamLog,			    //�޸Ĳ�����־
	StatInfo,					//���ͳ����Ϣ��־
	AlgorithmDLL				//�㷨����־
};
// �ɼ�ͼ������
enum e_GrabImageType	
{
	BodyImage = 0,	    // ƿ��
	BottomImage		// ƿ��
};
//����ͼ������
enum e_SaveImageType
{
	NotSave = 0,
	AllImage,
	FailureImage,
	AllImageInCount,
	FailureImageInCount,
};

// ������
enum e_CameraType	
{
	Camera1 = 0,	 
	Camera2,
	Camera3,
	Camera4		
};

//��ǰ����״̬
enum e_DrawStatus	
{
	DRAW_Status_NULL = 0,			//�޲���
	DRAW_Status_MOVE,				//�ƶ�
	DRAW_Status_ZOOM,				//����
	DRAW_Status_MODIFY,				//�޸�
};


//��ǰ���λ�����ڵ�
enum e_DrawSelect	
{
	DRAW_Select_NULL = 0,			//�޲�����
	DRAW_Select_MOVE,				//�ƶ���
	DRAW_Select_ZOOM,				//���ŵ�
	DRAW_Select_MODIFY,				//�޸ĵ�
};
//Ȩ��
typedef struct _Permission
{
	int iClear;
	int iExit;
	int iStartStop;
	int iImageCarve;
	int iVarietyManege;
	int iSystemSet;
	int iPLCSet;
	int iAlgSet;
	_Permission()
	{
		iClear = 0;
		iExit = 0;
		iStartStop = 0;
		iImageCarve = 0;
		iVarietyManege = 0;
		iSystemSet = 0;
		iPLCSet = 0;
		iAlgSet = 0;
	}
	void clear()
	{
		iClear = 0;
		iExit = 0;
		iStartStop = 0;
		iImageCarve = 0;
		iVarietyManege = 0;
		iSystemSet = 0;
		iPLCSet = 0;
		iAlgSet = 0;
	}
}s_Permission;
//ѡȡ��
typedef struct _SelectPoint
{
	int iX;
	int iY;
	int iOffset;
	_SelectPoint()
	{
		iX = 0;
		iY = 0;
		iOffset = 5;
	}
}s_SelectPoint;

//���νṹ��
typedef struct _RectangleShape
{
	int ileftupX;
	int ileftupY;
	int iWidth;
	int iHeight;
	_RectangleShape()
	{
		ileftupX = 0;
		ileftupY = 0;
		iWidth = 1;
		iHeight = 1;
	}
	_RectangleShape(QRect rt)
	{
		ileftupX = rt.x();
		ileftupY = rt.y();
		iWidth = rt.width();
		iHeight = rt.height();
	}
}s_RectangleShape;

typedef struct _IOSignal 
{
	short iGrabCount;				//ͼ���
	short iGrabDelay;				//�ɼ���ʱ
	_IOSignal()
	{
		iGrabCount = 0;
		iGrabDelay = 0;
	}
}s_IOSignal;

typedef struct _ResultInfo
{
public:
	int nIOCardNum;
	int nCamNo;
	int nImgNo;
	double dCostTime;
	int tmpResult;

	_ResultInfo()
	{
		nIOCardNum  = 0;
		nCamNo = 0;
		nImgNo = 0;
		dCostTime = 0;
		tmpResult = 0;
	}
}s_ResultInfo;

#endif // COMMON_H