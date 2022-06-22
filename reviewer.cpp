#include "reviewer.h"
Reviewer* pMainFrm;
Reviewer::Reviewer(QWidget *parent)
	: QMainWindow(parent)
{
	pMainFrm = this;
	ui.setupUi(this);
	initInterface();
	InitCheckSet();
}

Reviewer::~Reviewer()
{

}
void Reviewer::initLastData()
{
	QSettings LoadLastData(m_sConfigInfo.m_strDataPath,QSettings::IniFormat);
	LoadLastData.setIniCodec(QTextCodec::codecForName("GBK"));
	QString strSession;
	for (int j = 1;j<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;j++)
	{
		for (int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
		{
			strSession = QString("DefaultTypeCount/EveryRow%1").arg(i);
			int xRowTemp=LoadLastData.value(strSession,-1).toInt();

			strSession = QString("DefaultTypeCount/EveryLine%1").arg(j);
			int yLineTemp=LoadLastData.value(strSession,-1).toInt();

			if ( xRowTemp == -1 || yLineTemp == -1 )
			{
				continue;
			}

			strSession = QString("DefaultTypeCount/EveryNumber%1_%2").arg(xRowTemp).arg(yLineTemp);
			m_sRunningInfo.m_cErrorTypeInfo[xRowTemp].iErrorCountByType[yLineTemp]=LoadLastData.value(strSession,0).toInt();
			m_sRunningInfo.m_iErrorTypeCount[j]+=m_sRunningInfo.m_cErrorTypeInfo[xRowTemp].iErrorCountByType[yLineTemp];
			m_sRunningInfo.m_iErrorCamCount[i]+=m_sRunningInfo.m_cErrorTypeInfo[xRowTemp].iErrorCountByType[yLineTemp];
		}
	}
	strSession=QString("HeadCount/Checknumber");
	m_sRunningInfo.m_checkedNum=LoadLastData.value(strSession,0).toInt();

	strSession=QString("HeadCount/Failurenumber");
	m_sRunningInfo.m_failureNumFromIOcard=LoadLastData.value(strSession,0).toInt();

	//上一次整点数据
	strSession = QString("LastTimeDate/LastTime");
	LastTime=QDateTime::fromString(LoadLastData.value(strSession,"0000-00-00 00:00").toString(),"yyyy-MM-dd hh:mm");
	strSession = QString("LastTimeDate/Checknumber");
	LastTimeData.m_AllCount = LoadLastData.value(strSession,0).toInt();
	strSession = QString("LastTimeDate/Failurenumber");
	LastTimeData.m_FailCount = LoadLastData.value(strSession,0).toInt();

	for (int i=1;i<ERRORTYPE_MAX_COUNT;i++)
	{
		strSession = QString("LastTimeDate/ErrorType_%1_count").arg(i);
		LastTimeData.m_CameraTypeCount[i] = LoadLastData.value(strSession,0).toInt();
	}
	for (int i=1;i<CAMERA_MAX_COUNT;i++)
	{
		for(int j=1;j<ERRORTYPE_MAX_COUNT;j++)
		{
			strSession = QString("LastTimeDate/Camera%1_ErrorType%2").arg(i).arg(j);
			LastTimeData.m_TypeCount[i][j] = LoadLastData.value(strSession,0).toInt();
		}
	}
	//加载对应模板里的长宽并写入到配置文件中
	QSettings iniCameraSet(m_sSystemInfo.m_strModelName,QSettings::IniFormat);
	iniCameraSet.setIniCodec(QTextCodec::codecForName("GBK"));
	for(int i =0;i<m_sSystemInfo.iRealCamCount;i++)
	{
		m_sRealCamInfo[i].m_iImageWidth = iniCameraSet.value(QString("/width/Grab_%1").arg(i),0).toInt();
		m_sRealCamInfo[i].m_iImageHeight = iniCameraSet.value(QString("/height/Grab_%1").arg(i),0).toInt();
		QString tempFile = m_sConfigInfo.m_strAppPath + QString("Config/SimulateGrabberConfig%1.ini").arg(i+1);
		StateTool::WritePrivateProfileQString(QString::fromLocal8Bit("采图参数"),QString::fromLocal8Bit("图像宽度"),QString::number(m_sRealCamInfo[i].m_iImageWidth),tempFile);
		StateTool::WritePrivateProfileQString(QString::fromLocal8Bit("采图参数"),QString::fromLocal8Bit("图像高度"),QString::number(m_sRealCamInfo[i].m_iImageHeight),tempFile);
	}
}
void WINAPI GlobalGrabOverCallback (const s_GBSIGNALINFO* SigInfo)
{
	if (SigInfo && SigInfo->Context)
	{
		Reviewer* pGlassware = (Reviewer*) SigInfo->Context;
		pGlassware->GrabCallBack(SigInfo);
	}
}
void Reviewer::GrabCallBack(const s_GBSIGNALINFO *SigInfo)
{
	int iRealCameraSN = SigInfo->nGrabberSN;
	if (iRealCameraSN==-1 || !m_sRunningInfo.m_bCheck)
	{
		return;
	}
	if(SigInfo->nErrorCode != GBOK)
	{
		s_GBERRORINFO ErrorInfo;
		m_sRealCamInfo[iRealCameraSN].m_pGrabber->GetLastErrorInfo(&ErrorInfo);
		QString str = QString((QString("Camera:%1,")+QString("Error code:%2,")+QString("Error description:%3,")+QString("Additional information:%4")).arg(iRealCameraSN+1).arg(ErrorInfo.nErrorCode).arg(ErrorInfo.strErrorDescription).arg(ErrorInfo.strErrorRemark));		
		Logfile.write(QString("GrabCallBack:") + str ,CheckLog);
		return;
	}
	if(m_sRealCamInfo[iRealCameraSN].m_iImageIdxLast[0] == widget_carveSetting->image_widget->NCamCount)
	{
		return;
	}
	int imgNumber = ++m_sRealCamInfo[iRealCameraSN].m_iImageIdxLast[0];
	if (imgNumber >= 256)
	{
		imgNumber = 0;
	}
	//******************采集:得到图像缓冲区地址****************************//
	uchar* pImageBuffer = NULL;
	int nAddr = 0;
	int nWidth, nHeight;
	mutexDetectElement[iRealCameraSN].lock();
	m_sRealCamInfo[iRealCameraSN].m_pGrabber->GetParamInt(GBImageBufferAddr, nAddr);
	pImageBuffer = (uchar*)nAddr;
	m_sRealCamInfo[iRealCameraSN].m_pGrabber->GetParamInt(GBImageWidth, nWidth);
	m_sRealCamInfo[iRealCameraSN].m_pGrabber->GetParamInt(GBImageHeight, nHeight);
	mutexDetectElement[iRealCameraSN].unlock();

	CGrabElement *pGrabElement = NULL;
	if(nQueue[iRealCameraSN].listGrab.count()>0)
	{
		pMainFrm->nQueue[iRealCameraSN].mGrabLocker.lock();
		pGrabElement = (CGrabElement *) nQueue[iRealCameraSN].listGrab.first();
		nQueue[iRealCameraSN].listGrab.removeFirst();
		memcpy(pGrabElement->SourceImage->bits(),pImageBuffer,nWidth*nHeight);
		pMainFrm->nQueue[iRealCameraSN].mGrabLocker.unlock();
		pGrabElement->bHaveImage=TRUE;
		pGrabElement->nCheckRet = FALSE;
		pGrabElement->cErrorParaList.clear();
		pGrabElement->nWidth = nWidth;
		pGrabElement->nHeight = nHeight;
		pGrabElement->nSignalNo = imgNumber;
		pGrabElement->nCamSN = iRealCameraSN;
		if (nQueue[iRealCameraSN].InitID == pGrabElement->initID)
		{
			m_detectElement[iRealCameraSN].ImageNormal = pGrabElement;
			m_detectElement[iRealCameraSN].iCameraNormal = iRealCameraSN;
			m_detectElement[iRealCameraSN].iType = m_sCarvedCamInfo[iRealCameraSN].m_iStress;
			nQueue[iRealCameraSN].mDetectLocker.lock();
			nQueue[iRealCameraSN].listDetect.append(m_detectElement[iRealCameraSN]);
			nQueue[iRealCameraSN].mDetectLocker.unlock();
		}
		else
		{
			delete pGrabElement;
		}
	}
}
void Reviewer::initInterface()
{
	qRegisterMetaType<e_SaveLogType>("e_SaveLogType");  
	qRegisterMetaType<QList<QRect>>("QList<QRect>");
	QString path = QApplication::applicationFilePath();  
	m_sConfigInfo.m_strAppPath = path.left(path.findRev("/")+1);
	//配置文件在run目录中位置
	m_sConfigInfo.m_strConfigPath = m_sConfigInfo.m_strAppPath + "Config/Config.ini";
	m_sConfigInfo.m_strDataPath = m_sConfigInfo.m_strAppPath + "Config/Data1.ini";
	m_sConfigInfo.m_strErrorTypePath = m_sConfigInfo.m_strAppPath + "Config/ErrorType.ini";
	m_sConfigInfo.m_sAlgFilePath = m_sConfigInfo.m_strAppPath + "ModelInfo";
	
	QSettings iniset(m_sConfigInfo.m_strConfigPath,QSettings::IniFormat);
	iniset.setIniCodec(QTextCodec::codecForName("GBK"));
	QSettings erroriniset(m_sConfigInfo.m_strErrorTypePath,QSettings::IniFormat);
	erroriniset.setIniCodec(QTextCodec::codecForName("GBK"));
	QSettings iniDataSet(m_sConfigInfo.m_strDataPath,QSettings::IniFormat);
	iniDataSet.setIniCodec(QTextCodec::codecForName("GBK"));

	QString strSession;
	strSession = QString("/ErrorType/total");
	m_sErrorInfo.m_iErrorTypeCount = erroriniset.value("/ErrorType/total",0).toInt();

	for (int i=0;i<=m_sErrorInfo.m_iErrorTypeCount;i++)
	{
		if (0 == i)
		{
			m_sErrorInfo.m_bErrorType[i] = false;
			m_sErrorInfo.m_vstrErrorType.append(tr("Good"));//.toLatin1().data()));
		}
		else
		{
			m_sErrorInfo.m_bErrorType[i] = true;
			strSession = QString("/ErrorType/%1").arg(i);
			m_sErrorInfo.m_vstrErrorType.append(QString::fromLocal8Bit(erroriniset.value(strSession,"NULL").toString()));//.toLatin1().data()));
			m_sErrorInfo.m_cErrorReject.iErrorCountByType[i] = 0;
		}
	}
	m_vcolorTable.clear();
	for (int i = 0; i < 256; i++)  
	{
		m_vcolorTable.append(qRgb(i, i, i)); 
	}
	//读取系统参数
	m_sSystemInfo.IsCarve = iniset.value("/system/IsCarve",false).toBool();
	m_sSystemInfo.m_strWindowTitle = QObject::tr("Glass Bottle Detect System");//读取系统标题
	m_sSystemInfo.m_iTest = iniset.value("/system/Test",0).toInt();
	m_sSystemInfo.iRealCamCount = iniset.value("/GarbCardParameter/DeviceNum",2).toInt();	//真实相机个数
	m_sSystemInfo.LastModelName = iniset.value("/system/LastModelName","default").toString();	//读取上次使用模板
	
	int iShift[3];
	iShift[0] = iniset.value("/system/shift1",000000).toInt();
	iShift[1] = iniset.value("/system/shift2",80000).toInt();
	iShift[2] = iniset.value("/system/shift3",160000).toInt();
	for (int i = 0; i<2; i++)
	{
		if (iShift[i] > iShift[i+1] )
		{
			int temp =iShift[i];
			iShift[i] = iShift[i+1];
			iShift[i+1] = temp;
		}
	}
	m_sSystemInfo.shift1.setHMS(iShift[0]/10000,(iShift[0]%10000)/100,iShift[0]%100);
	m_sSystemInfo.shift2.setHMS(iShift[1]/10000,(iShift[1]%10000)/100,iShift[1]%100);
	m_sSystemInfo.shift3.setHMS(iShift[2]/10000,(iShift[2]%10000)/100,iShift[2]%100);
	m_sConfigInfo.m_strGrabInfoPath = m_sConfigInfo.m_strAppPath + "ModelInfo/" + m_sSystemInfo.LastModelName + "/GrabInfo.ini";
	m_sSystemInfo.m_strModelName = m_sConfigInfo.m_strGrabInfoPath;
	//切割后相机个数
	m_sSystemInfo.iCamCount = iniset.value("/system/CarveDeviceCount",1).toInt();
	m_sSystemInfo.m_iTrackNumber = 0;
	initLastData();
	for (int i=0;i<m_sSystemInfo.iCamCount;i++)
	{
		pdetthread[i] = NULL;
		m_sRealCamInfo[i].m_bGrabIsStart = FALSE;
		m_pHandles[i] = CreateEvent(NULL,FALSE,NULL,NULL);
	}

	for (int i=0;i<m_sSystemInfo.iRealCamCount;i++)
	{
		struGrabCardPara[i].iGrabberTypeSN = i;
		struGrabCardPara[i].nGrabberSN = iniset.value(QString("/GarbCardParameter/Device%1ID").arg(i+1),-1).toInt();
		strcpy_s(struGrabCardPara[i].strDeviceName,"SimulaGrab");
		strcpy_s(struGrabCardPara[i].strDeviceMark,"6735372222222220609");
		m_sRealCamInfo[i].m_iImageRoAngle = iniset.value(QString("/RoAngle/Device_%1").arg(i+1),0).toInt();
		m_sRealCamInfo[i].m_iImageType = iniset.value(QString("/ImageType/Device_%1").arg(i+1),0).toInt();
		QString strGrabInitFile = m_sConfigInfo.m_strConfigPath.left(m_sConfigInfo.m_strConfigPath.findRev("/")+1) + QString("SimulateGrabberConfig%1.ini").arg(i+1);
		memcpy(struGrabCardPara[i].strGrabberFile,strGrabInitFile.toLocal8Bit().data(),GBMaxTextLen);
	}
	
	for (int i=0;i<m_sSystemInfo.iCamCount;i++)
	{
		pdetthread[i] = new DetectThread(this,i);
		m_bIsThreadDead = FALSE;
		pdetthread[i]->start();
	}
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	setMinimumSize(screenRect.width()*2/3,screenRect.height()*2/3);

	statked_widget = new QStackedWidget();
	statked_widget->setObjectName("mainStacked");
	title_widget = new WidgetTitle(this);
	widget_carveSetting = new WidgetCarveSetting;
	Count_widget = new Widget_Count;
	widget_alg = new QWidget(this);
	widget_alg->setObjectName("widget_alg");

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::white));
	statked_widget->setPalette(palette);
	statked_widget->setAutoFillBackground(true);
	statked_widget->addWidget(widget_carveSetting);
	statked_widget->addWidget(Count_widget);
	statked_widget->addWidget(widget_alg);

	stateBar = new QWidget(this);
	stateBar->setFixedHeight(20);
	QFont fontCoder;
	fontCoder.setPixelSize(28);
	labelCoder = new QLabel(stateBar);
	labelCoder->setFont(fontCoder);
	labelCoder->setText(QString::fromLocal8Bit(m_sSystemInfo.LastModelName));

	QHBoxLayout* hLayoutStateBar = new QHBoxLayout(stateBar);
	hLayoutStateBar->addStretch();
	hLayoutStateBar->addWidget(labelCoder);
	hLayoutStateBar->setSpacing(3);
	hLayoutStateBar->setContentsMargins(10, 0, 10, 0);

	QHBoxLayout *center_layout = new QHBoxLayout();
	center_layout->addWidget(statked_widget);
	center_layout->setSpacing(0);
	center_layout->setContentsMargins(5,5,5,5);

	ui.verticalLayout->addWidget(title_widget);
	ui.verticalLayout->addLayout(center_layout);
	ui.verticalLayout->addWidget(stateBar);
	ui.verticalLayout->setSpacing(0);
	ui.verticalLayout->setContentsMargins(0, 0, 0, 0);

	connect(title_widget, SIGNAL(turnPage(int)), this, SLOT(slots_turnPage(int)));

	for (int i=0;i<m_sSystemInfo.iRealCamCount;i++)
	{
		struGrabCardPara[i].CallBackFunc = GlobalGrabOverCallback;
		struGrabCardPara[i].Context = this;
		InitGrabCard(struGrabCardPara[i],i);
	}
	for (int i = 0;i<m_sSystemInfo.iRealCamCount;i++)
	{
		m_sRealCamInfo[i].m_pGrabber->StartGrab();
		m_sRealCamInfo[i].m_bGrabIsStart=TRUE;
	}
	InitImage();
}
void Reviewer::InitGrabCard(s_GBINITSTRUCT struGrabCardPara,int index)
{
	QString strDeviceName = QString(struGrabCardPara.strDeviceName);
	if (strDeviceName=="SimulaGrab")
	{
		m_sRealCamInfo[index].m_pGrabber = new CDHGrabberSG;
		m_sRealCamInfo[index].m_bSmuGrabber = true;
		m_sRealCamInfo[index].m_iGrabType = 0;
	}
	
	BOOL bRet = FALSE;
	try
	{
		bRet = m_sRealCamInfo[index].m_pGrabber->Init(&struGrabCardPara);	
		if(bRet)
		{
			m_sRealCamInfo[index].m_bCameraInitSuccess=TRUE;
			bRet = m_sRealCamInfo[index].m_pGrabber->GetParamInt(GBImageWidth, m_sRealCamInfo[index].m_iImageWidth);
			if(bRet)
			{
				bRet = m_sRealCamInfo[index].m_pGrabber->GetParamInt(GBImageHeight, m_sRealCamInfo[index].m_iImageHeight);
				if(bRet)
				{
					bRet = m_sRealCamInfo[index].m_pGrabber->GetParamInt(GBImageBufferSize, m_sRealCamInfo[index].m_iImageSize);	
					if(bRet)
					{
						int nImagePixelSize = 0;
						bRet = m_sRealCamInfo[index].m_pGrabber->GetParamInt(GBImagePixelSize, nImagePixelSize);
						m_sRealCamInfo[index].m_iImageBitCount = 8* nImagePixelSize;	
					}
				}
			}		
		}
	}
	catch (...)
	{
		QString strError;
		strError = QString("catch camera%1 initial error").arg(index);
		m_sRealCamInfo[index].m_bCameraInitSuccess = FALSE;
	}

	if (bRet)
	{
		m_sRealCamInfo[index].m_bCameraInitSuccess = TRUE;
		if(m_sSystemInfo.m_iSystemType != 2)
		{
			m_sRealCamInfo[index+m_sSystemInfo.iRealCamCount].m_bCameraInitSuccess = m_sRealCamInfo[index].m_bCameraInitSuccess;
			m_sRealCamInfo[index+m_sSystemInfo.iRealCamCount].m_iImageWidth = m_sRealCamInfo[index].m_iImageWidth;
			m_sRealCamInfo[index+m_sSystemInfo.iRealCamCount].m_iImageHeight = m_sRealCamInfo[index].m_iImageHeight;
			m_sRealCamInfo[index+m_sSystemInfo.iRealCamCount].m_iImageRoAngle = m_sRealCamInfo[index].m_iImageRoAngle;
			if (90 == m_sRealCamInfo[index].m_iImageRoAngle || 270 == m_sRealCamInfo[index].m_iImageRoAngle )
			{
				int iTemp = m_sRealCamInfo[index+m_sSystemInfo.iRealCamCount].m_iImageHeight;
				m_sRealCamInfo[index+m_sSystemInfo.iRealCamCount].m_iImageHeight = m_sRealCamInfo[index+m_sSystemInfo.iRealCamCount].m_iImageWidth;
				m_sRealCamInfo[index+m_sSystemInfo.iRealCamCount].m_iImageWidth = iTemp;
			}
		}
	}
	else
	{
		m_sRealCamInfo[index].m_bCameraInitSuccess = FALSE;
		s_GBERRORINFO ErrorInfo;
		QString str;			
		m_sRealCamInfo[index].m_pGrabber->GetLastErrorInfo(&ErrorInfo);
		str = tr("DeviceName:%1").arg(strDeviceName)+"\n"+tr("ErrorCode:%2").arg(ErrorInfo.nErrorCode)+"\n"+
			tr("ErrorDescription:%3").arg(QString::fromLocal8Bit(ErrorInfo.strErrorDescription))+"\n"+tr("ErrorRemark:%4\n").arg(QString::fromLocal8Bit(ErrorInfo.strErrorRemark));
		QMessageBox::information(this,tr("Error"),str);
		m_sRealCamInfo[index].m_strErrorInfo = str;
		if(m_sSystemInfo.m_iSystemType != 2)
		{
			m_sRealCamInfo[index+m_sSystemInfo.iRealCamCount].m_bCameraInitSuccess = m_sRealCamInfo[index].m_bCameraInitSuccess;
		}
	}
	if (90 == m_sRealCamInfo[index].m_iImageRoAngle || 270 == m_sRealCamInfo[index].m_iImageRoAngle )
	{
		int iTemp = m_sRealCamInfo[index].m_iImageHeight;
		m_sRealCamInfo[index].m_iImageHeight = m_sRealCamInfo[index].m_iImageWidth;
		m_sRealCamInfo[index].m_iImageWidth = iTemp;
	}
}
void Reviewer::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) 
	{
		return;
	}
}
void Reviewer::slots_load()
{

}
bool Reviewer::RoAngle(uchar* pRes,uchar* pTar,int iResWidth,int iResHeight,int iAngle)
{
	int iTarWidth;
	int iTarHeight;
	if(pRes == NULL || iResWidth == 0 || iResHeight == 0)
	{
		return FALSE;
	}
	if (iAngle == 90)
	{
		iTarWidth = iResHeight;
		iTarHeight = iResWidth;
		for (int i=0;i<iResHeight;i++)
		{
			for (int j=0;j<iResWidth;j++) 
			{
				*(pTar+j*iTarWidth+(iTarWidth-i-1)) = *(pRes+i*iResWidth+j);
			}
		}
	}
	if (iAngle == 270)
	{	
		iTarWidth = iResHeight;
		iTarHeight = iResWidth;
		for (int i=0;i<iResHeight;i++)
		{
			for (int j=0;j<iResWidth;j++) 
			{
				*(pTar+(iTarHeight-j-1)*iTarWidth+i) = *(pRes+i*iResWidth+j);
			}
		}
	}
	if (iAngle == 180)
	{
		iTarWidth = iResWidth;
		iTarHeight = iResHeight;
		for (int i=0;i<iResHeight;i++)
		{
			for (int j=0;j<iResWidth;j++) 
			{
				*(pTar+(iTarHeight-i-1)*iTarWidth+(iTarWidth-j-1))=*(pRes+i*iResWidth+j);
			}
		}
	}
	return TRUE;
}
void Reviewer::CarveImage(uchar* pRes,uchar* pTar,int iResWidth,int iResHeight,int iTarX,int iTarY,int iTarWidth,int iTarHeight)
{
	try
	{
		uchar* pTemp = pTar;
		uchar* pTempRes = pRes+iResWidth*(iTarY)+iTarX;
		for(int i = 0; i < iTarHeight; i++)
		{
			memcpy(pTemp,pTempRes,iTarWidth);
			pTemp += iTarWidth;
			pTempRes += iResWidth;
		}
	}
	catch(...)
	{
		Logfile.write(("Error in image carve "),AbnormityLog);
	}
}
void Reviewer::slots_turnPage(int current_page, int iPara)
{
	if (m_sRunningInfo.m_eLastMainPage == current_page)
	{
		return;
	}
	/*if(current_page == 0 || current_page == 1)
	{
		s_Status  sReturnStatus;
		sReturnStatus = m_cBottleModel.CloseModelDlg();
		if (0 != sReturnStatus.nErrorID)
		{
			return ;
		}
	}*/

	switch (current_page)
	{
	case 0:
		statked_widget->setCurrentWidget(widget_carveSetting);
		m_sRunningInfo.m_eLastMainPage = CarveSettingPage;
		pMainFrm->Logfile.write(("into CarveSetting"),AbnormityLog);
		break;
	case 1:
		statked_widget->setCurrentWidget(Count_widget);
		m_sRunningInfo.m_eLastMainPage = CountPage;
		pMainFrm->Logfile.write(("into widgetCount"),AbnormityLog);
		break;
	case 2:
		break;
	case 3:
		statked_widget->setCurrentWidget(widget_alg);
		ShowCheckSet(iPara);
		m_sRunningInfo.m_eLastMainPage = AlgPage;
		pMainFrm->Logfile.write(("into AlgPage"),AbnormityLog);
		break;
	case 4:
		slots_OnBtnStar();
		break;
	case 5:
		if (QMessageBox::Yes== QMessageBox::question(this,tr("Exit"),tr("Are you sure to clear?"),QMessageBox::Yes | QMessageBox::No))	
		{
			slots_Clear();
		}
		break;
	case 6:
		break;
	}
}
void Reviewer::slots_Clear()
{
	m_sRunningInfo.m_failureNumFromIOcard = 0;
	m_sRunningInfo.m_checkedNum = 0;
}
void Reviewer::slots_OnBtnStar()
{
	ToolButton *TBtn = title_widget->button_list.at(4);
	if (!m_sRunningInfo.m_bCheck )//开始检测
	{
		//图像综合清零
		m_cCombine.m_MutexCombin.lock();
		m_cCombine.RemovAllResult();
		m_cCombine.RemovAllError();
		m_cCombine.m_MutexCombin.unlock();
		pMainFrm->m_sSystemInfo.m_iTrackNumber = 0;
		if (m_sSystemInfo.m_bLoadModel)
		{
			for (int i = 0; i < m_sSystemInfo.iCamCount;i++)
			{
				m_sRealCamInfo[i].m_iImageIdxLast[0] = 0;
				m_sRealCamInfo[i].m_iImageIdxLast[1] = 0;
			}
			m_sRunningInfo.nGSoap_ErrorTypeCount[0]=0;
			m_sRunningInfo.nGSoap_ErrorCamCount[0]=0;
			m_sRunningInfo.nGSoap_ErrorTypeCount[2]=0;
			m_sRunningInfo.nGSoap_ErrorCamCount[2]=0;
			pMainFrm->Logfile.write(("Start Check"),OperationLog);
		}
		else
		{
			QMessageBox::information(this,tr("Error"),tr("No Model,Please Load Model!"));
			return;
		}
		QPixmap pixmap(":/toolWidget/stop");
		TBtn->setText(tr("Stop"));
		TBtn->setIcon(pixmap);
		TBtn->bStatus = true;
		m_sRunningInfo.m_bCheck = true;
	}

	else if (m_sRunningInfo.m_bCheck)//停止检测
	{
		m_sRunningInfo.m_bCheck = false;
		pMainFrm->Logfile.write(("Stop Check"),OperationLog);
		QPixmap pixmap(":/toolWidget/start");
		TBtn->setText(tr("Start"));
		TBtn->setIcon(pixmap);

		for (int i = 0;i<m_sSystemInfo.iCamCount;i++)
		{
			s_SystemInfoforAlg sSystemInfoforAlg;
			sSystemInfoforAlg.bIsChecking = false;
			m_cBottleCheck[i].setsSystemInfo(sSystemInfoforAlg);
		}
		TBtn->bStatus = false;
	}
}
void Reviewer::SaveLastData()
{
	QSettings iniDataSet(m_sConfigInfo.m_strDataPath,QSettings::IniFormat);
	iniDataSet.setIniCodec(QTextCodec::codecForName("GBK"));
	iniDataSet.setValue("system/checkedNum",m_sRunningInfo.m_checkedNum);
	iniDataSet.setValue("system/failureNum",m_sRunningInfo.m_failureNumFromIOcard);
	for (int i=0;i< m_sSystemInfo.iCamCount;i++)
	{
		iniDataSet.setValue(QString("LastTimeDate/ErrorCamera_%1_count").arg(i),m_sRunningInfo.m_iErrorCamCount[i]);
	}
}
void Reviewer::closeEvent(QCloseEvent *e)
{
	m_bIsThreadDead = TRUE;
	SaveLastData();
}
void Reviewer::InitCheckSet()
{
	//算法初始化，模板调入等 [8/4/2010 GZ]
	s_Status  sReturnStatus;
	s_AlgInitParam   sAlgInitParam;	
	if(m_sSystemInfo.m_iMaxCameraImageWidth>m_sSystemInfo.m_iMaxCameraImageHeight)
	{
		sReturnStatus = init_bottle_module(m_sSystemInfo.m_iMaxCameraImageWidth,m_sSystemInfo.m_iMaxCameraImageWidth,1);
	}
	else
	{
		sReturnStatus = init_bottle_module(m_sSystemInfo.m_iMaxCameraImageHeight,m_sSystemInfo.m_iMaxCameraImageHeight,1);
	}
	if (sReturnStatus.nErrorID != RETURN_OK)
	{
		pMainFrm->Logfile.write(tr("----load model error----"),AbnormityLog);
		return;
	}	
	for (int i=0;i<m_sSystemInfo.iCamCount;i++)
	{
		sAlgInitParam.nCamIndex=i;
		sAlgInitParam.nModelType = m_sRealCamInfo[i].m_iImageType;  //检测类型
		sAlgInitParam.nWidth = m_sRealCamInfo[i].m_iImageWidth; 
		sAlgInitParam.nHeight =  m_sRealCamInfo[i].m_iImageHeight;
		memset(sAlgInitParam.chCurrentPath,0,MAX_PATH);

		strcpy_s(sAlgInitParam.chCurrentPath,m_sConfigInfo.m_sAlgFilePath.toLocal8Bit()); 
		memset(sAlgInitParam.chModelName,0,MAX_PATH); //模板名称
		strcpy_s(sAlgInitParam.chModelName,m_sSystemInfo.m_strModelName.toLocal8Bit()); 
		sReturnStatus = m_cBottleCheck[i].init(sAlgInitParam);

		if (sReturnStatus.nErrorID != RETURN_OK && sReturnStatus.nErrorID != 1)
		{
			pMainFrm->Logfile.write(tr("----camera%1 load model error----").arg(i),AbnormityLog);
			return;
		}
		if (sReturnStatus.nErrorID == 1)
		{
			m_sSystemInfo.m_bLoadModel =  FALSE;  //如果模板为空，则不能检测 
		}
		else
		{
			m_sSystemInfo.m_bLoadModel =  TRUE;  //成功载入上一次的模板
		}
		sAlgInitParam.nModelType = 99;  //检测类型
		memset(sAlgInitParam.chModelName,0,MAX_PATH); //模板名称
		m_cBottleRotate[i].init(sAlgInitParam);
		sAlgInitParam.nModelType = 98;  //检测类型
		m_cBottleStress[i].init(sAlgInitParam);
	}
	if (CherkerAry.pCheckerlist != NULL)
	{
		delete[] CherkerAry.pCheckerlist;
	}
	CherkerAry.iValidNum = m_sSystemInfo.iCamCount;
	CherkerAry.pCheckerlist = new s_CheckerList[CherkerAry.iValidNum];
}
void Reviewer::InitImage()
{
	for (int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		m_sCarvedCamInfo[i].m_iResImageWidth = m_sRealCamInfo[i].m_iImageWidth;
		m_sCarvedCamInfo[i].m_iResImageHeight = m_sRealCamInfo[i].m_iImageHeight;
		m_sCarvedCamInfo[i].m_iImageType = m_sRealCamInfo[i].m_iImageType;
	}

	//获取最大图像信息
	for (int i=0;i<m_sSystemInfo.iRealCamCount;i++)
	{
		if (i==0)
		{
			m_sSystemInfo.m_iMaxCameraImageWidth     = m_sRealCamInfo[i].m_iImageWidth;
			m_sSystemInfo.m_iMaxCameraImageHeight    = m_sRealCamInfo[i].m_iImageHeight;
			m_sSystemInfo.m_iMaxCameraImageSize      = m_sRealCamInfo[i].m_iImageSize;
			m_sSystemInfo.m_iMaxCameraImagePixelSize = (m_sRealCamInfo[i].m_iImageBitCount+7)/8;
		}
		else
		{
			if (m_sRealCamInfo[i].m_iImageWidth > m_sSystemInfo.m_iMaxCameraImageWidth)
			{
				m_sSystemInfo.m_iMaxCameraImageWidth = m_sRealCamInfo[i].m_iImageWidth;
			}				
			if (m_sRealCamInfo[i].m_iImageHeight > m_sSystemInfo.m_iMaxCameraImageHeight)
			{
				m_sSystemInfo.m_iMaxCameraImageHeight = m_sRealCamInfo[i].m_iImageHeight;
			}				
			if (((m_sRealCamInfo[i].m_iImageBitCount+7)/8) > m_sSystemInfo.m_iMaxCameraImagePixelSize)
			{
				m_sSystemInfo.m_iMaxCameraImagePixelSize = ((m_sRealCamInfo[i].m_iImageBitCount+7)/8);
			}			
		}
		m_sSystemInfo.m_iMaxCameraImageSize = m_sSystemInfo.m_iMaxCameraImageWidth*m_sSystemInfo.m_iMaxCameraImageHeight;
	}
	ReadCorveConfig();
	QString strSession;
	for(int i = 0 ; i < m_sSystemInfo.iCamCount; i++)
	{
		//分配原始图像空间：每真实相机1个，剪切图像使用
		if (m_sRealCamInfo[i].m_pRealImage!=NULL)
		{
			delete m_sRealCamInfo[i].m_pRealImage;
			m_sRealCamInfo[i].m_pRealImage = NULL;
		}

		m_sRealCamInfo[i].m_pRealImage=new QImage(m_sRealCamInfo[i].m_iImageWidth,m_sRealCamInfo[i].m_iImageHeight,m_sRealCamInfo[i].m_iImageBitCount);// 用于实时显示

		if (8 == m_sRealCamInfo[i].m_iImageBitCount)
		{
			m_sRealCamInfo[i].m_pRealImage->setColorTable(m_vcolorTable);
		}

		memset(m_sRealCamInfo[i].m_pRealImage->bits(),0, m_sRealCamInfo[i].m_pRealImage->byteCount());

		m_sCarvedCamInfo[i].m_iImageBitCount = m_sRealCamInfo[i].m_iImageBitCount;   //图像位数从相机处继承[8/7/2013 nanjc]
		m_sCarvedCamInfo[i].m_iImageRoAngle = m_sRealCamInfo[i].m_iImageRoAngle;
		// 错误统计用类
		m_sRunningInfo.m_cErrorTypeInfo[i].m_iErrorTypeCount = m_sErrorInfo.m_iErrorTypeCount;

		//实时显示用, 预分配QImage空间，每切出相机一个
		if (m_sCarvedCamInfo[i].m_pActiveImage!=NULL)
		{
			delete m_sCarvedCamInfo[i].m_pActiveImage;
			m_sCarvedCamInfo[i].m_pActiveImage = NULL;
		}

		m_sCarvedCamInfo[i].m_pActiveImage=new QImage(m_sCarvedCamInfo[i].m_iImageWidth,m_sCarvedCamInfo[i].m_iImageHeight,m_sCarvedCamInfo[i].m_iImageBitCount);// 用于实时显示

		m_sCarvedCamInfo[i].m_pActiveImage->setColorTable(m_vcolorTable);
		//开始采集前补一张黑图
		BYTE* pByte = m_sCarvedCamInfo[i].m_pActiveImage->bits();
		int iLength = m_sCarvedCamInfo[i].m_pActiveImage->byteCount();
		memset((pByte),0,(iLength));
		//分配图像剪切内存区域,大小等于真实相机大小
		if (m_sCarvedCamInfo[i].m_pGrabTemp!=NULL)
		{
			delete m_sCarvedCamInfo[i].m_pGrabTemp; 
			m_sCarvedCamInfo[i].m_pGrabTemp = NULL;
		}
		m_sCarvedCamInfo[i].m_pGrabTemp = new BYTE[m_sRealCamInfo[i].m_iImageWidth*m_sRealCamInfo[i].m_iImageHeight];
		//分配元素链表中图像的内存，每剪切出来的相机10个。
		nQueue[i].InitCarveQueue(m_sCarvedCamInfo[i].m_iImageWidth, m_sCarvedCamInfo[i].m_iImageHeight,m_sRealCamInfo[i].m_iImageWidth,m_sRealCamInfo[i].m_iImageHeight,m_sCarvedCamInfo[i].m_iImageBitCount, 10, true);
		for (int k = 0; k < 256;k++)
		{
			delete []m_sCarvedCamInfo[i].sImageLocInfo[k].m_AlgImageLocInfos.sXldPoint.nColsAry;
			delete []m_sCarvedCamInfo[i].sImageLocInfo[k].m_AlgImageLocInfos.sXldPoint.nRowsAry;

			m_sCarvedCamInfo[i].sImageLocInfo[k].m_iHaveInfo = 0;
			m_sCarvedCamInfo[i].sImageLocInfo[k].m_AlgImageLocInfos.sXldPoint.nCount = 0;
			m_sCarvedCamInfo[i].sImageLocInfo[k].m_AlgImageLocInfos.sXldPoint.nRowsAry = new int[BOTTLEXLD_POINTNUM];
			m_sCarvedCamInfo[i].sImageLocInfo[k].m_AlgImageLocInfos.sXldPoint.nColsAry = new int[BOTTLEXLD_POINTNUM];
			memset(m_sCarvedCamInfo[i].sImageLocInfo[k].m_AlgImageLocInfos.sXldPoint.nRowsAry,0, 4*BOTTLEXLD_POINTNUM);
			memset(m_sCarvedCamInfo[i].sImageLocInfo[k].m_AlgImageLocInfos.sXldPoint.nColsAry,0, 4*BOTTLEXLD_POINTNUM);
			// 				memset
		}
	}
	SetCarvedCamInfo();
	//初始化缺陷图像列表
	m_ErrorList.initErrorList(m_sSystemInfo.m_iMaxCameraImageWidth,m_sSystemInfo.m_iMaxCameraImageHeight,m_sSystemInfo.m_iMaxCameraImagePixelSize*8,ERROR_IMAGE_COUNT,true);
}
void Reviewer::ReadCorveConfig()
{
	QSettings iniCarveSet(m_sConfigInfo.m_strGrabInfoPath,QSettings::IniFormat);
	QString strSession;
	for(int i=0; i < pMainFrm->m_sSystemInfo.iCamCount; i++)
	{
		//加载剪切后参数
		strSession = QString("/angle/Grab_%1").arg(i);
		m_sCarvedCamInfo[i].m_iImageAngle = iniCarveSet.value(strSession,0).toInt();
		strSession = QString("/Stress/Device_%1").arg(i);
		m_sCarvedCamInfo[i].m_iStress = iniCarveSet.value(strSession,0).toInt();
		strSession = QString("/tonormal/Grab_%1").arg(i);
		m_sCarvedCamInfo[i].m_iToNormalCamera = iniCarveSet.value(strSession,i).toInt();
		strSession = QString("/pointx/Grab_%1").arg(i);
		m_sCarvedCamInfo[i].i_ImageX = 0;
		strSession = QString("/pointy/Grab_%1").arg(i);
		m_sCarvedCamInfo[i].i_ImageY = 0;
		strSession = QString("/width/Grab_%1").arg(i);
		m_sCarvedCamInfo[i].m_iImageWidth = iniCarveSet.value(strSession,500).toInt();
		strSession = QString("/height/Grab_%1").arg(i);
		m_sCarvedCamInfo[i].m_iImageHeight = iniCarveSet.value(strSession,500).toInt();
		strSession = QString("/convert/Grab_%1").arg(i);
		m_sCarvedCamInfo[i].m_iToRealCamera = iniCarveSet.value(strSession,i).toInt();
		if ((m_sCarvedCamInfo[i].i_ImageX + m_sCarvedCamInfo[i].m_iImageWidth) > m_sRealCamInfo[i].m_iImageWidth)
		{
			m_sCarvedCamInfo[i].i_ImageX = 0;
			m_sCarvedCamInfo[i].m_iImageWidth = m_sRealCamInfo[i].m_iImageWidth;
		}
		if ((m_sCarvedCamInfo[i].i_ImageY + m_sCarvedCamInfo[i].m_iImageHeight) > m_sRealCamInfo[i].m_iImageHeight)
		{
			m_sCarvedCamInfo[i].i_ImageY = 0;
			m_sCarvedCamInfo[i].m_iImageHeight = m_sRealCamInfo[i].m_iImageHeight;
		}
	}
}
void Reviewer::SetCarvedCamInfo()
{
	for (int i = 0;i<m_sSystemInfo.iCamCount;i++)
	{
		m_sCarvedCamInfo[i].m_iResImageWidth = m_sRealCamInfo[i].m_iImageWidth;
		m_sCarvedCamInfo[i].m_iResImageHeight = m_sRealCamInfo[i].m_iImageHeight;
		m_sCarvedCamInfo[i].m_iImageType = m_sRealCamInfo[i].m_iImageType;
	}
	//设置图像综合参数
	for (int i = 0;i<m_sSystemInfo.iCamCount;i++)
	{
		m_cCombine.SetCombineCamera(i,true);
		m_sSystemInfo.IOCardiCamCount[0]++;
	}
	m_cCombine.Inital(m_sSystemInfo.IOCardiCamCount[0]);
}
void Reviewer::ShowCheckSet(int nCamIdx,int signalNumber)
{
	try
	{
		s_AlgModelPara  sAlgModelPara;	
		QImage tempIamge;

		if(widget_carveSetting->image_widget->bIsShowErrorImage[nCamIdx]&&pMainFrm->m_SavePicture[nCamIdx].pThat!=NULL)
		{
			tempIamge=pMainFrm->m_SavePicture[nCamIdx].m_Picture;
			sAlgModelPara.sImgLocInfo = widget_carveSetting->image_widget->sAlgImageLocInfo[nCamIdx];
		}else{
			pMainFrm->nQueue[nCamIdx].mGrabLocker.lock();
			if(pMainFrm->nQueue[nCamIdx].listGrab.size()==0)
			{
				pMainFrm->nQueue[nCamIdx].mGrabLocker.unlock();
				return;
			}
			CGrabElement *pElement = pMainFrm->nQueue[nCamIdx].listGrab.last();
			tempIamge = (*pElement->myImage);
			sAlgModelPara.sImgLocInfo = pElement->sImgLocInfo;
			pMainFrm->nQueue[nCamIdx].mGrabLocker.unlock();
		}
		m_cBottleModel.CloseModelDlg();
		sAlgModelPara.sImgPara.nChannel = 1;
		sAlgModelPara.sImgPara.nHeight = tempIamge.height();
		sAlgModelPara.sImgPara.nWidth = tempIamge.width();
		sAlgModelPara.sImgPara.pcData = (char*)tempIamge.bits();

		if (sAlgModelPara.sImgPara.nHeight != pMainFrm->m_sCarvedCamInfo[nCamIdx].m_iImageHeight)
		{
			return;
		}
		if (sAlgModelPara.sImgPara.nWidth != pMainFrm->m_sCarvedCamInfo[nCamIdx].m_iImageWidth)
		{
			return;
		}		

		for (int i=0;i<m_sSystemInfo.iCamCount;i++)
		{
			CherkerAry.pCheckerlist[i].nID = i;
			CherkerAry.pCheckerlist[i].pChecker = &m_cBottleCheck[i];
		}	
		int widthd = widget_alg->geometry().width();
		int heightd	= widget_alg->geometry().height();
		if (widthd < 150 || heightd < 150)
		{
			return;
		}	
		s_Status  sReturnStatus = m_cBottleModel.SetModelDlg(sAlgModelPara,&m_cBottleCheck[nCamIdx],CherkerAry,widget_alg);
		if (sReturnStatus.nErrorID != RETURN_OK)
		{
			return;
		}
		statked_widget->setCurrentWidget(widget_alg);
		m_sRunningInfo.m_eLastMainPage = AlgPage;
	}
	catch (...)
	{
	}
	pMainFrm->Logfile.write(("Into Alg Page")+QString("CamraNo:%1").arg(nCamIdx+1),OperationLog,0);
	return;	
}

