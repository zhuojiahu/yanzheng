/************************************************************************/
/* Copyright (c) 2013, �й���㼯�ű���ͼ���Ӿ������ֹ�˾�Ӿ�ϵͳ��  
/* All rights reserved.													
/*																		
/* �ļ����ƣ� DHGrabberForMER.h	
/* ժҪ�� �����ɼ����ࣨ��˾ˮ�������

/* ��ǰ�汾��1.0.0.3
/* �޸��ߣ���ͬ
/* ��Ҫ�޸����ݣ�ʵ�ֻ����ĳ�ʼ���������ɼ���ֹͣ�ɼ�����֡�ɼ��Ͳ������ý��� ���ֺ����滻Ϊ�°�sdk����
/* ������ڣ�2016��7��15��

/************************************************************************/

#if !defined(DHGrabber_h_)
#define DHGrabber_h_
#include "stdint.h"
/*
�ɼ������ͱ�Ŷ�������
0:ģ��ɼ���
1:DALSA X64�ɼ���
2:AVT���
3:ǧ�������
4:��˾CG300ģ��ɼ���
5:��˾1394���
6:EURESYS �ɼ���
7:��˾USB���
8::��˾ˮ��ϵ�����*/

const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;
typedef struct _GBSignalInfoStruct//�ص���Ϣ�ṹ
{
	PVOID Context;								//���ӵ�лص������Ķ����thisָ��
	int iGrabberTypeSN;							// �ɼ������ͱ��
	int nGrabberSN;								//������ص����к�
	int nErrorCode;								//������루0��������
	int nFrameCount;							//�Ѳɼ���֡����
	char strDescription[GBMaxTextLen];			//������Ϣ

	int iReserve1;								// �����ֶ�1
	int iReserve2;							// �����ֶ�2
}s_GBSIGNALINFO;//�ص���Ϣ�ṹ

//�ص�����ָ������
typedef void (WINAPI *PGBCALLBACK)(const s_GBSIGNALINFO* SignalInfo);

typedef struct _GBInitStruct//�ɼ�����ʼ���ṹ
{
	int iGrabberTypeSN;						// �ɼ������ͱ��
	int nGrabberSN;							//�ɼ������
    char strDeviceName[GBMaxTextLen];		//�豸����
	char strDeviceMark[GBMaxTextLen];		// �豸��ʶ
	char strGrabberFile[GBMaxFileNameLen];	//���ڳ�ʼ�����ļ�
	PGBCALLBACK CallBackFunc;				//�ص�����ָ��
	PVOID Context;							//���ӵ�лص������Ķ����thisָ��
	
	int iReserve1;							// �����ֶ�1
	int iReserve2;							// �����ֶ�2

}s_GBINITSTRUCT;//�ɼ�����ʼ���ṹ

typedef struct _GBErrorInfoStruct//������Ϣ�ṹ
{
   	int nErrorCode;							//������루0��������
	char strErrorDescription[GBMaxTextLen];	//��������
	char strErrorRemark[GBMaxTextLen];		//������Ϣ

}s_GBERRORINFO;//������Ϣ�ṹ

//��������
enum GBParamID
{
	GBImageWidth = 0,		//ͼ���� (��λ:�ֽ�)
	GBImageHeight,			//ͼ��߶� (��λ:�ֽ�)
	GBImagePixelSize,		//ͼ�����ش�С (��λ:�ֽ�)
	GBImageBufferSize,		//ͼ�񻺳�����С (��λ:�ֽ�)
	GBImageBufferAddr,		//ͼ�񻺳�����ַ
	GBGrabberTypeSN			//�ɼ������ͱ��
};

//������붨��
const int GBOK = 0;

class CGrabber
{
//����
public:
	CGrabber()
	{
	}
	virtual ~CGrabber()
	{
	}
	
	//��ʼ��
	virtual BOOL Init(const s_GBINITSTRUCT* pInitParam) = 0;

	//�ر�
	virtual BOOL Close() = 0;

	//��ʼ�ɼ�
	virtual BOOL StartGrab() = 0;

	//ֹͣ�ɼ�
	virtual BOOL StopGrab() = 0;
	
	//��֡�ɼ�
	virtual BOOL Snapshot() = 0;

	//���ò���
	virtual BOOL SetParamInt(GBParamID Param, int nInputVal) = 0;
	
	//�õ�����
	virtual BOOL GetParamInt(GBParamID Param, int &nOutputVal) = 0;
	
	//���ò����Ի���
	virtual void CallParamDialog() = 0;
	
	//�õ�������Ϣ
	virtual void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo) = 0;
};

#endif// !defined(DHGrabber_h_)

#if !defined(DHGrabberSG_h_)
#define DHGrabberSG_h_

//////////////////////////////////////////////////////////////////////////
//ģ��ɼ���ר�в���

//ģ��ɼ�������
enum SGParamID
{
	SGIsPlaneRGB = 0,		//�Ƿ��ͨ�� (0����1����)
	SGGrabSpeed,			//��ͼ�ٶ� (��λ:����/��)
	SGImageWidth,			//ͼ���� (��λ:����)//[2006-12-01]
	SGImageHeight,			//ͼ��߶� (��λ:����)//[2006-12-01]
	SGImageByteCount,		//ͼ��ÿ�����ֽ��� (��λ:�ֽ�)//[2006-12-01]
};

//������붨��
const int SGErrorCodeInitFileNoExist = 1000;	//��ʼ���ļ�������
const int SGErrorCodeParamIll = 1001;			//�������Ϸ�
const int SGErrorCodeInitFileParamIll = 1002;	//��ʼ���ļ��������Ϸ�
const int SGErrorCodeNoInit = 1003;				//����δ��ʼ��
const int SGErrorCodeThisFuncDisable = 1004;	//�˹�����Ч
const int SGErrorCodeReadBMPFileFail = 1200;	//��BMP�ļ�ʧ��
const int SGErrorCodeReadImageFromMemFail = 1201;	//���ڴ��ж�ȡͼ��ʧ��//[2006-08-23]
//
//////////////////////////////////////////////////////////////////////////

//�ɼ���
class _declspec(dllimport) CDHGrabberSG : public CGrabber
{
//����
public:
	CDHGrabberSG();
	virtual ~CDHGrabberSG();
	
	//��ʼ��
	BOOL Init(const s_GBINITSTRUCT* pInitParam);

	//�ر�
	BOOL Close();

	//��ʼ�ɼ�
	BOOL StartGrab();

	//ֹͣ�ɼ�
	BOOL StopGrab();

	//��֡�ɼ�
	BOOL Snapshot();
	
	//���ò���
	BOOL SetParamInt(GBParamID Param, int nInputVal);
	
	//�õ�����
	BOOL GetParamInt(GBParamID Param, int &nOutputVal);

	//���ò����Ի���
	void CallParamDialog();

	//�õ�������Ϣ
	void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo);

	//////////////////////////////////////////////////////////////////////////
	//ģ��ɼ���ר�нӿ�

	BOOL SGSetParamInt(SGParamID Param, int nInputVal);
	BOOL SGGetParamInt(SGParamID Param, int &nOutputVal);
	//
	//////////////////////////////////////////////////////////////////////////
	
//����
protected:
	CGrabber *m_pGrabber;
};

#endif// !defined(DHGrabberSG_h_)