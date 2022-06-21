#include "DetectThread.h"
#include <QMessageBox>
#include <math.h>
#include "reviewer.h"
extern Reviewer *pMainFrm;

DetectThread::DetectThread(QObject *parent,int temp)
	: QThread(parent),tempOri()
{
	m_threadId = temp;
	m_bStopThread = false;
	dirSaveImagePath = new QDir;
	iMaxErrorType = 0;
	iMaxErrorArea = 0;
	iErrorType = 0;
}
DetectThread::~DetectThread()
{
	delete dirSaveImagePath;
}
void DetectThread::run()
{
	while (!pMainFrm->m_bIsThreadDead)
	{
		if(!m_bStopThread)
		{
			ProcessHanlde(m_threadId);		
		}
		Sleep(1);
	}
}
void DetectThread::ProcessHanlde(int Camera)
{
	if(pMainFrm->nQueue[Camera].listDetect.length()>0)
	{
		pMainFrm->nQueue[Camera].mDetectLocker.lock();
		CDetectElement DetectElement = pMainFrm->nQueue[Camera].listDetect.first();
		pMainFrm->nQueue[Camera].listDetect.removeFirst();
		pMainFrm->nQueue[Camera].mDetectLocker.unlock();
		iCamera = DetectElement.iCameraNormal;
		//��תԭʼͼƬ
		if (90 == pMainFrm->m_sRealCamInfo[iCamera].m_iImageRoAngle || 180 == pMainFrm->m_sRealCamInfo[iCamera].m_iImageRoAngle || 270 == pMainFrm->m_sRealCamInfo[iCamera].m_iImageRoAngle)
		{
			pMainFrm->RoAngle(DetectElement.ImageNormal->SourceImage->bits(), pMainFrm->m_sRealCamInfo[iCamera].m_pRealImage->bits(), \
				DetectElement.ImageNormal->nWidth, DetectElement.ImageNormal->nHeight, pMainFrm->m_sRealCamInfo[iCamera].m_iImageRoAngle);
		}
		else
		{
			memcpy(pMainFrm->m_sRealCamInfo[iCamera].m_pRealImage->bits(), DetectElement.ImageNormal->SourceImage->bits(), pMainFrm->m_sRealCamInfo[iCamera].m_iImageWidth * pMainFrm->m_sRealCamInfo[iCamera].m_iImageHeight);
		}
		//�ü�ԭʼͼƬ
		pMainFrm->m_mutexmCarve[iCamera].lock();
		long lImageSize = pMainFrm->m_sCarvedCamInfo[iCamera].m_iImageWidth * pMainFrm->m_sCarvedCamInfo[iCamera].m_iImageHeight;
		if (lImageSize != DetectElement.ImageNormal->myImage->byteCount())
		{
			pMainFrm->Logfile.write(tr("ImageSize unsuitable, Thread:Grab, camera:%1.lImageSize = %2,myImage byteCount = %3").arg(iCamera).arg(lImageSize).arg(DetectElement.ImageNormal->myImage->byteCount()),AbnormityLog);
			delete DetectElement.ImageNormal->myImage;
			delete DetectElement.ImageNormal->SourceImage;
			DetectElement.ImageNormal->myImage = NULL;
			DetectElement.ImageNormal->SourceImage = NULL;
			delete DetectElement.ImageNormal;
			pMainFrm->m_mutexmCarve[iCamera].unlock();
			return;
		}
		pMainFrm->CarveImage(pMainFrm->m_sRealCamInfo[iCamera].m_pRealImage->bits(),pMainFrm->m_sCarvedCamInfo[iCamera].m_pGrabTemp,\
			pMainFrm->m_sRealCamInfo[iCamera].m_iImageWidth,pMainFrm->m_sRealCamInfo[iCamera].m_iImageHeight, pMainFrm->m_sCarvedCamInfo[iCamera].i_ImageX,pMainFrm->m_sCarvedCamInfo[iCamera].i_ImageY,\
			pMainFrm->m_sCarvedCamInfo[iCamera].m_iImageWidth,pMainFrm->m_sCarvedCamInfo[iCamera].m_iImageHeight);			

		memcpy(DetectElement.ImageNormal->myImage->bits(), pMainFrm->m_sCarvedCamInfo[iCamera].m_pGrabTemp, \
			pMainFrm->m_sCarvedCamInfo[iCamera].m_iImageWidth*pMainFrm->m_sCarvedCamInfo[iCamera].m_iImageHeight);
		//�����⻷��
		pMainFrm->m_mutexmCarve[iCamera].unlock();
		
		DetectNormal(DetectElement.ImageNormal,DetectElement.iType);
		if (pMainFrm->nQueue[iCamera].InitID == DetectElement.ImageNormal->initID)
		{ 
			pMainFrm->nQueue[iCamera].mGrabLocker.lock();
			pMainFrm->nQueue[iCamera].listGrab.push_back(DetectElement.ImageNormal);
			pMainFrm->nQueue[iCamera].mGrabLocker.unlock();
		}
		else
		{
			delete DetectElement.ImageNormal->SourceImage;
			delete DetectElement.ImageNormal->myImage;
			DetectElement.ImageNormal->myImage = NULL;
			DetectElement.ImageNormal->SourceImage = NULL;
			delete DetectElement.ImageNormal;
		}
	}
}
void DetectThread::DetectNormal(CGrabElement *pElement,int nTmp)
{
	checkTimecost.StartSpeedTest();
	bCheckResult[iCamera] = false;
	iErrorType = 0;
	iMaxErrorType = 0;
	iMaxErrorArea = 0;
	pElement->cErrorRectList.clear();
	//rotateImage(pElement);
	if (pMainFrm->m_sRunningInfo.m_bCheck && pMainFrm->m_sRunningInfo.m_bIsCheck[iCamera])
	{
		try
		{
			checkImage(pElement,nTmp);
			bool bOK = getCheckResult(pElement);
			if (!bOK)
			{
				return;
			}
		}
		catch (...)
		{
			pMainFrm->Logfile.write("Algorithm crash!",CheckLog);
		}
	}
	CountDefectIOCard(pElement->nSignalNo,bCheckResult[iCamera]);
	//saveImage(pElement);
	//������ͼ������������
	if (bCheckResult[iCamera])
	{
		addErrorImageList(pElement);
	}
	checkTimecost.StopSpeedTest();
	pElement->dCostTime = checkTimecost.dfTime;

	//ˢ��ͼ���״̬
	if(pMainFrm->nQueue[iCamera].InitID == pElement->initID)
	{
		upDateState(pElement->myImage,pElement->nSignalNo,pElement->dCostTime, pElement->nMouldID, pElement->cErrorRectList,pElement->initID);
	}
	pElement = NULL;
}
//��תͼ��
void DetectThread::rotateImage(CGrabElement *pElement)
{
	sAlgCInp.sInputParam.nWidth = pElement->myImage->width();
	sAlgCInp.sInputParam.nHeight = pElement->myImage->height();
	sAlgCInp.sInputParam.pcData = (char*)pElement->myImage->bits();
	if(pMainFrm->m_sCarvedCamInfo[iCamera].m_iImageAngle != 0)
	{
		sAlgCInp.nParam = pMainFrm->m_sCarvedCamInfo[iCamera].m_iImageAngle;
		pMainFrm->m_cBottleRotate[iCamera].Check(sAlgCInp, &pAlgCheckResult);
	}
}
//���
void DetectThread::checkImage(CGrabElement *pElement,int iCheckMode)
{
	sAlgCInp.sInputParam.nHeight = pElement->myImage->height();
	sAlgCInp.sInputParam.nWidth = pElement->myImage->width();
	sAlgCInp.sInputParam.nChannel = 1;
	sAlgCInp.sInputParam.pcData = (char*)pElement->myImage->bits();
	//sReturnStatus = pMainFrm->m_cBottleCheck[iCamera].Check(sAlgCInp,&pAlgCheckResult);

	if (0 == iCheckMode)
	{
		sReturnStatus = pMainFrm->m_cBottleCheck[iCamera].Check(sAlgCInp,&pAlgCheckResult);
		pMainFrm->m_sCarvedCamInfo[iCamera].sImageLocInfo[pElement->nSignalNo].m_AlgImageLocInfos.sLocOri = pAlgCheckResult->sImgLocInfo.sLocOri;
		pMainFrm->m_sCarvedCamInfo[iCamera].sImageLocInfo[pElement->nSignalNo].m_AlgImageLocInfos.sXldPoint.nCount  = pAlgCheckResult->sImgLocInfo.sXldPoint.nCount;
		memcpy(pMainFrm->m_sCarvedCamInfo[iCamera].sImageLocInfo[pElement->nSignalNo].m_AlgImageLocInfos.sXldPoint.nColsAry, \
			pAlgCheckResult->sImgLocInfo.sXldPoint.nColsAry,4*BOTTLEXLD_POINTNUM);														
		memcpy(pMainFrm->m_sCarvedCamInfo[iCamera].sImageLocInfo[pElement->nSignalNo].m_AlgImageLocInfos.sXldPoint.nRowsAry, \
			pAlgCheckResult->sImgLocInfo.sXldPoint.nRowsAry,4*BOTTLEXLD_POINTNUM);
		
		SetEvent(pMainFrm->m_pHandles[iCamera]);
		pMainFrm->m_sCarvedCamInfo[iCamera].sImageLocInfo[pElement->nSignalNo].m_iHaveInfo = 1;
	}
	else if (1 == iCheckMode)
	{
		int normalCamera = pMainFrm->m_sCarvedCamInfo[iCamera].m_iToNormalCamera;
		if(!pMainFrm->m_sSystemInfo.m_bIsTest)
		{
			int dwRet = WaitForSingleObject(pMainFrm->m_pHandles[normalCamera],1500);
			switch(dwRet)
			{
			case WAIT_TIMEOUT:
				sReturnStatus.nErrorID = 1;
				pMainFrm->Logfile.write(QString("Camera:%1 overtime").arg(iCamera+1) ,CheckLog);
				return;
			}
		}
		
		pElement->sImgLocInfo.sLocOri = pMainFrm->m_sCarvedCamInfo[normalCamera].sImageLocInfo[pElement->nSignalNo].m_AlgImageLocInfos.sLocOri;
		pElement->sImgLocInfo.sXldPoint.nCount = pMainFrm->m_sCarvedCamInfo[normalCamera].sImageLocInfo[pElement->nSignalNo].m_AlgImageLocInfos.sXldPoint.nCount;

		memcpy(pElement->sImgLocInfo.sXldPoint.nColsAry,\
			pMainFrm->m_sCarvedCamInfo[normalCamera].sImageLocInfo[pElement->nSignalNo].m_AlgImageLocInfos.sXldPoint.nColsAry,4*BOTTLEXLD_POINTNUM);							
		memcpy(pElement->sImgLocInfo.sXldPoint.nRowsAry,\
			pMainFrm->m_sCarvedCamInfo[normalCamera].sImageLocInfo[pElement->nSignalNo].m_AlgImageLocInfos.sXldPoint.nRowsAry,4*BOTTLEXLD_POINTNUM);
		
		if(pElement->sImgLocInfo.sLocOri.modelCol == 0 || pElement->sImgLocInfo.sLocOri.modelRow == 0)
		{
			pElement->sImgLocInfo.sLocOri = tempOri;
		}else{
			tempOri = pElement->sImgLocInfo.sLocOri;
		}
		sAlgCInp.sImgLocInfo = pElement->sImgLocInfo;
		sReturnStatus = pMainFrm->m_cBottleCheck[iCamera].Check(sAlgCInp,&pAlgCheckResult);
		pMainFrm->m_sCarvedCamInfo[ pMainFrm->m_sCarvedCamInfo[iCamera].m_iToNormalCamera].sImageLocInfo[pElement->nSignalNo].m_iHaveInfo = 0;
	}
	else
	{
		sReturnStatus = pMainFrm->m_cBottleCheck[iCamera].Check(sAlgCInp,&pAlgCheckResult);
	}
}
//��ȡ�����
bool DetectThread::getCheckResult(CGrabElement *pElement)
{
	if (sReturnStatus.nErrorID != 0)
	{
		return false;
	}
	//��ȡ���ģ���������
	GetModelDotData(pElement);
	if (pAlgCheckResult->nSizeError >0) //�д����Ҵ����δ�رռ��
	{
		//������ƿͳ��
		bCheckResult[iCamera] = true;
		pElement->cErrorParaList.clear(); //�����

		for (int j=0;j<pAlgCheckResult->nSizeError;j++) //����㷨���ش����������
		{
			s_ErrorPara  sErrorPara;
			sErrorPara = pAlgCheckResult->vErrorParaAry[j];
			if(sErrorPara.nArea > iMaxErrorArea)
			{
				iMaxErrorArea = sErrorPara.nArea;
				iMaxErrorType = sErrorPara.nErrorType;
			}
			QRect rect(sErrorPara.rRctError.left,sErrorPara.rRctError.top,sErrorPara.rRctError.right - sErrorPara.rRctError.left,sErrorPara.rRctError.bottom - sErrorPara.rRctError.top);
			if (iMaxErrorType > pMainFrm->m_sErrorInfo.m_iErrorTypeCount)
			{
				iMaxErrorType = pMainFrm->m_sErrorInfo.m_iErrorTypeCount+1;
				sErrorPara.nErrorType = pMainFrm->m_sErrorInfo.m_iErrorTypeCount+1;
			}
			//	�Ҳ���ԭ�㲻�߷�
			
			if(sErrorPara.nErrorType==39)
			{
				bCheckResult[iCamera] = true;
			}
			//���㷨���ش�������������
			if (bCheckResult[iCamera])
			{
				pElement->cErrorRectList.append(rect);
				pElement->cErrorParaList.append(sErrorPara);
				emit signals_upDateCamera(iCamera,1 );
			}
			pMainFrm->m_cCombine.AddError(pElement->nSignalNo,iCamera,sErrorPara);
		}	

		iErrorType = iMaxErrorType;
		pElement->nCheckRet = iErrorType;
	}
	else//û�д������
	{
		emit signals_upDateCamera(iCamera,0);
		s_ErrorPara sErrorPara;
		sErrorPara.nArea = 0;
		sErrorPara.nErrorType = 0;
		//pMainFrm->m_cCombine.m_MutexCombin.lock();
		pMainFrm->m_cCombine.AddError(pElement->nSignalNo,iCamera,sErrorPara);
		//pMainFrm->m_cCombine.m_MutexCombin.unlock();
	}
	return true;
}
void DetectThread::CountDefectIOCard(int nSignalNo,int tmpResult)
{
	int comResult = -1;//�ۺϺ�Ľ��
	pMainFrm->m_cCombine.AddResult(nSignalNo,iCamera,tmpResult);
	if (pMainFrm->m_cCombine.ConbineResult(nSignalNo,0,comResult))//ͼ����������ۺ�
	{
		pMainFrm->m_cCombine.SetReject(nSignalNo);
		pMainFrm->m_cCombine.RemoveOneResult(nSignalNo);
		pMainFrm->m_sRunningInfo.m_checkedNum++;
		if(bCheckResult[iCamera])
		{
			pMainFrm->m_sRunningInfo.m_failureNumFromIOcard++;
		}
		if (pMainFrm->m_sRunningInfo.m_bCheck)	
		{
			int iErrorCamera = pMainFrm->m_cCombine.ErrorCamera(nSignalNo);
			s_ErrorPara sComErrorpara = pMainFrm->m_cCombine.ConbineError(nSignalNo);
			if (pMainFrm->m_sRunningInfo.m_cErrorTypeInfo[iErrorCamera].ErrorTypeJudge(sComErrorpara.nErrorType))
			{
				pMainFrm->m_sRunningInfo.m_cErrorTypeInfo[iErrorCamera].iErrorCountByType[sComErrorpara.nErrorType]+=1;
				pMainFrm->m_sRunningInfo.m_iErrorCamCount[iErrorCamera] += 1;//ȱ���������
				pMainFrm->m_sRunningInfo.m_iErrorTypeCount[sComErrorpara.nErrorType] +=1;//ÿ��ȱ�ݵļ���ͳ��
			}
		}
	}
}

void DetectThread::saveImage(CGrabElement *pElement)
{
	if (1 == pMainFrm->m_sSystemInfo.m_iSaveNormalErrorImageByTime)
	{
		if (bCheckResult[iCamera])
		{
			QDateTime time = QDateTime::currentDateTime();
			QString strSaveImagePath = QString(pMainFrm->m_sConfigInfo.m_strAppPath + tr("SaveImageByTime\\") +\
				tr("normal image\\") + time.date().toString("yyyy-MM-dd") + tr("\\camera%1").arg(iCamera+1)) + "\\" + time.time().toString("hh");
			bool exist = dirSaveImagePath->exists(strSaveImagePath);
			if(!exist)
			{
				dirSaveImagePath->mkpath(strSaveImagePath);
			}
			QString strSavePath = QString(strSaveImagePath + "/image number%1_%2%3%4_%5.bmp").arg(iCamera+1).arg(pElement->nSignalNo).arg(time.time().hour()).arg(time.time().minute()).arg(time.time().second());
			pElement->myImage->mirrored().save(strSavePath);
		}
	}
	if (1 == pMainFrm->m_sSystemInfo.m_iSaveStressErrorImageByTime)
	{
		if (bCheckResult[iCamera])
		{
			QDateTime time = QDateTime::currentDateTime();
			QString strSaveImagePath = QString(pMainFrm->m_sConfigInfo.m_strAppPath + tr("SaveImageByTime\\") +\
				tr("stress image\\") + time.date().toString("yyyy-MM-dd") + tr("\\camera%1").arg(iCamera+1)) + "\\" + time.time().toString("hh");
			bool exist = dirSaveImagePath->exists(strSaveImagePath);
			if(!exist)
			{
				dirSaveImagePath->mkpath(strSaveImagePath);
			}
			QString strSavePath = QString(strSaveImagePath + "/image number%1_%2%3%4_%5.bmp").arg(iCamera+1).arg(pElement->nSignalNo).arg(time.time().hour()).arg(time.time().minute()).arg(time.time().second());
			pElement->myImage->mirrored().save(strSavePath);
		}

	}
	if (AllImage == pMainFrm->m_sRunningInfo.m_eSaveImageType || AllImageInCount == pMainFrm->m_sRunningInfo.m_eSaveImageType)
	{
		if (0 == pMainFrm->m_sSystemInfo.m_bSaveCamera[iCamera])
		{
			return;
		}
		QTime time = QTime::currentTime();
		QString strSaveImagePath = QString(pMainFrm->m_sConfigInfo.m_strAppPath + "SaveImage/All-image/camera%1/").arg(iCamera+1);
		bool exist = dirSaveImagePath->exists(strSaveImagePath);
		if(!exist)
		{
			dirSaveImagePath->mkpath(strSaveImagePath);
		}
		if (AllImage == pMainFrm->m_sRunningInfo.m_eSaveImageType)
		{
			QString strSavePath = QString(strSaveImagePath + "image_%1_%2%3%4_%5_%6.bmp").arg(iCamera+1).arg(pElement->nSignalNo).arg(time.hour()).arg(time.minute()).arg(time.second()).arg(time.msec());
			pElement->myImage->mirrored().save(strSavePath);
		}
		if (AllImageInCount == pMainFrm->m_sRunningInfo.m_eSaveImageType)
		{
			pMainFrm->m_sRunningInfo.m_mutexRunningInfo.lock();
			if (pMainFrm->m_sRunningInfo.m_iSaveImgCount[iCamera] > 0)
			{
				QString strSavePath = QString(strSaveImagePath + "image_%1_%2%3%4_%5_%6.bmp").arg(iCamera+1).arg(pElement->nSignalNo).arg(time.hour()).arg(time.minute()).arg(time.second()).arg(time.msec());
				pElement->myImage->mirrored().save(strSavePath);
				pMainFrm->m_sRunningInfo.m_iSaveImgCount[iCamera]--;
			}
			int itempSavemode = 0;
			for (int i = 0 ; i<pMainFrm->m_sSystemInfo.iCamCount;i++)
			{
				if (pMainFrm->m_sSystemInfo.m_bSaveCamera[i] == 1)
				{
					itempSavemode = 1;
				}
			}
			if (0 == itempSavemode)
			{
				pMainFrm->m_sRunningInfo.m_eSaveImageType = NotSave;
			}
			pMainFrm->m_sRunningInfo.m_mutexRunningInfo.unlock();
		}
	}else if (FailureImage == pMainFrm->m_sRunningInfo.m_eSaveImageType||FailureImageInCount == pMainFrm->m_sRunningInfo.m_eSaveImageType)
	{
		if (0 == pMainFrm->m_sSystemInfo.m_bSaveCamera[iCamera])
		{
			return;
		}
		if (0 == pMainFrm->m_sSystemInfo.m_bSaveErrorType[iErrorType])
		{
			return;
		}
		QTime time = QTime::currentTime();
		QString strSaveImagePath = QString(pMainFrm->m_sConfigInfo.m_strAppPath + "SaveImage/Failure-image/camera%1").arg(iCamera+1);
		bool exist = dirSaveImagePath->exists(strSaveImagePath);
		if(!exist)
		{
			dirSaveImagePath->mkpath(strSaveImagePath);
		}
		if (FailureImage == pMainFrm->m_sRunningInfo.m_eSaveImageType)
		{
			QString strSavePath = QString(strSaveImagePath + "/image_%1_%2%3%4_%5_%6.bmp").arg(iCamera+1).arg(pElement->nSignalNo).arg(time.hour()).arg(time.minute()).arg(time.second()).arg(time.msec());
			pElement->myImage->mirrored().save(strSavePath);
		}
		if (FailureImageInCount == pMainFrm->m_sRunningInfo.m_eSaveImageType)
		{
			pMainFrm->m_sRunningInfo.m_mutexRunningInfo.lock();
			if (pMainFrm->m_sRunningInfo.m_iSaveImgCount[iCamera] > 0)
			{
				QString strSavePath = QString(strSaveImagePath + "/image_%1_%2%3%4_%5_%6.bmp").arg(iCamera+1).arg(pElement->nSignalNo).arg(time.hour()).arg(time.minute()).arg(time.second()).arg(time.msec());
				pElement->myImage->mirrored().save(strSavePath);
				pMainFrm->m_sRunningInfo.m_iSaveImgCount[iCamera]--;
			}
			if (0 == pMainFrm->m_sRunningInfo.m_iSaveImgCount[iCamera])
			{
				pMainFrm->m_sSystemInfo.m_bSaveCamera[iCamera] = 0;
			}
			int itempSavemode = 0;
			for (int i = 0 ; i<pMainFrm->m_sSystemInfo.iCamCount;i++)
			{
				if (pMainFrm->m_sSystemInfo.m_bSaveCamera[i] == 1)
				{
					itempSavemode = 1;
				}
			}
			if (0 == itempSavemode)
			{
				pMainFrm->m_sRunningInfo.m_eSaveImageType = NotSave;
			}
			pMainFrm->m_sRunningInfo.m_mutexRunningInfo.unlock();
		}
	}
}
//��ȱ��ͼ������������
void DetectThread::addErrorImageList(CGrabElement *pElement)
{
	pMainFrm->m_ErrorList.m_mutexmErrorList.lock();
	CGrabElement *pErrorElement = pMainFrm->m_ErrorList.listError.last();
	pMainFrm->m_ErrorList.listError.removeLast();
	pErrorElement->nCamSN = pElement->nCamSN;
	pErrorElement->dCostTime = pElement->dCostTime;
	pErrorElement->nCheckRet = pElement->nCheckRet;
	pErrorElement->nSignalNo = pElement->nSignalNo; 
	pErrorElement->cErrorRectList = pElement->cErrorRectList;
	pErrorElement->cErrorParaList = pElement->cErrorParaList;
	pErrorElement->sImgLocInfo.sLocOri = pElement->sImgLocInfo.sLocOri;
	pErrorElement->sImgLocInfo.sXldPoint.nCount = pElement->sImgLocInfo.sXldPoint.nCount;
	memcpy(pErrorElement->sImgLocInfo.sXldPoint.nColsAry,pElement->sImgLocInfo.sXldPoint.nColsAry,4*BOTTLEXLD_POINTNUM);							
	memcpy(pErrorElement->sImgLocInfo.sXldPoint.nRowsAry,pElement->sImgLocInfo.sXldPoint.nRowsAry,4*BOTTLEXLD_POINTNUM);
	//******************************************
	if (pErrorElement->myImage != NULL)
	{
		delete pErrorElement->myImage;
		pErrorElement->myImage = NULL;
	}
	pErrorElement->myImage = new QImage(*pElement->myImage);
	pMainFrm->m_ErrorList.listError.push_front(pErrorElement);
	pMainFrm->m_ErrorList.m_mutexmErrorList.unlock();

	emit signals_AddErrorTableView(pElement->nCamSN,pElement->nSignalNo,pElement->cErrorParaList.first().nErrorType);
}
//������ʾ״̬
void DetectThread::upDateState( QImage* myImage, int signalNo,double costTime, int nMouldID, QList<QRect> listErrorRectList,int ImageCount)
{
	QString camera = QString::number(iCamera);
	QString imageSN = QString::number(signalNo);
	QString time = QString::number(costTime,'f',2);
	QString result = pMainFrm->m_sErrorInfo.m_vstrErrorType.at(iErrorType);
	QString mouldID = QString::number(nMouldID);

	emit signals_updateActiveImg(iCamera,signalNo,costTime,iErrorType);//���¼��е�ͼ����ʾ
	emit signals_updateImage(myImage, camera, imageSN, time, result, mouldID, listErrorRectList, ImageCount);
}

void DetectThread::GetModelDotData(CGrabElement *pElement)
{
	pElement->nMouldID = pAlgCheckResult->nMouldID;
	if (pAlgCheckResult->nMouldID>0 && pAlgCheckResult->nMouldID < 100)
	{
		pMainFrm->m_sRunningInfo.nModelCheckedCount++;
	}
}