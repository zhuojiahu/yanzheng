#include "widget_count.h"
#include <QLayout>
#include <QStandardItem>
#include <QTextStream>
#include <ActiveQt/QAxObject>
#include <QMap>
#include "reviewer.h"
extern Reviewer *pMainFrm;
Widget_Count::Widget_Count(QWidget *parent)
	: QWidget(parent),m_TemporaryData()
{
	pStackedCount = new QStackedWidget();
	widgetCountSet = new CountSet;

	DHBaseWidget *widget = new DHBaseWidget;
	widget->setWidgetName(tr("Count Table"));

	//建立查看历史页面
	recordWidget = new QWidget();
	m_WidgetReport = new WidgetReport(recordWidget,pMainFrm->m_sSystemInfo.iCamCount);
	QGridLayout *scrollAreaGridLayout = new QGridLayout();
	scrollAreaGridLayout->addWidget(m_WidgetReport);
	scrollAreaGridLayout->setMargin(0);
	recordWidget->setLayout(scrollAreaGridLayout);
	//直方图报表
	//建立主页面
	pStackedCount->addWidget(recordWidget);
	QHBoxLayout *nameLayout = new QHBoxLayout;
	nameLayout->addWidget(widget->widgetName);

	QVBoxLayout *countLayout = new QVBoxLayout(widget);
	countLayout->addLayout(nameLayout);
	countLayout->addWidget(pStackedCount);
	countLayout->setSpacing(5);
	countLayout->setContentsMargins(5, 0, 5, 0);

	widgetCountSet->ui.widget_calendar->setWidgetName(tr("History"));
	widgetCountSet->ui.Layout_calendarTitle->addWidget(widgetCountSet->ui.widget_calendar->widgetName);
	widgetCountSet->ui.widget_saveRecord->setWidgetName(tr("Save Set"));
	widgetCountSet->ui.Layout_saveRecordTitle->addWidget(widgetCountSet->ui.widget_saveRecord->widgetName);
	widgetCountSet->ui.widget_shitf->setWidgetName(tr("Shift Set"));
	widgetCountSet->ui.Layout_shiftTitle->addWidget(widgetCountSet->ui.widget_shitf->widgetName);

	widgetCountSet->ui.calendarWidget->setLocale(QLocale::Chinese);
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(widget);
	mainLayout->addWidget(widgetCountSet);
	setLayout(mainLayout);
	isClear1 = false;
	isClear2 = false;
	isClear3 = false;

	shift1 = pMainFrm->m_sSystemInfo.shift1;
	shift2 = pMainFrm->m_sSystemInfo.shift2;
	shift3 = pMainFrm->m_sSystemInfo.shift3;
	QTime time = QTime::currentTime();
	int iTime = time.hour()*10000+time.minute()*100+time.second();
	int iShift1 = shift1.hour()*10000 + shift1.minute()*100 + shift1.second();
	int iShift2 = shift2.hour()*10000 + shift2.minute()*100 + shift2.second();
	int iShift3 = shift3.hour()*10000 + shift3.minute()*100 + shift3.second();
	if (iTime>iShift1 && iTime<iShift2)
	{
		isClear1 = true;
	}
	if (iTime>iShift2 && iTime<iShift3)
	{
		isClear2 = true;
	}	
	if (iTime<iShift1 || iTime>iShift3)
	{
		isClear3 = true;
	}
	init();
	for (int i=1;i<=pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		for(int j=1;j<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;j++)
		{
			m_lasterrorData[i][j]= pMainFrm->m_sErrorInfo.i_countErrorType[i][j];
		}
	}
}

Widget_Count::~Widget_Count()
{
	
}

void Widget_Count::init()
{
	//插入列表头
	for (int i=0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		connect(pMainFrm->pdetthread[i],SIGNAL(signals_SaveReport()),this,SLOT(slots_SaveCountInfo()));
	}
	initLastData();

	timerSaveHourList = new QTimer(this);
	timerSaveHourList->setInterval(60000);//每分钟触发一次
	timerSaveHourList->start();  	//启动定时器    

	if (bAutoSetZero)
	{
		connect(timerSaveHourList, SIGNAL(timeout()), this, SLOT(slots_timerClearCountInfo()));   
	}
	else
	{
		disconnect(timerSaveHourList, SIGNAL(timeout()), this, SLOT(slots_timerClearCountInfo()));   

	}
	connect(widgetCountSet->ui.pushButton_openRecord,SIGNAL(clicked()),this,SLOT(slots_OpenRecord()));
	connect(widgetCountSet->ui.pushButton_deleteRecord,SIGNAL(clicked()),this,SLOT(slots_DeleteRecord()));
	connect(widgetCountSet->ui.pushButton_saveRecordOK,SIGNAL(clicked()),this,SLOT(slots_saveRecordOK()));
	connect(widgetCountSet->ui.pushButton_saveRecordCancel,SIGNAL(clicked()),this,SLOT(slots_saveRecordCancel()));
	connect(widgetCountSet->ui.pushButton_shiftOK,SIGNAL(clicked()),this,SLOT(slots_shiftOK()));
	connect(widgetCountSet->ui.pushButton_shiftCancel,SIGNAL(clicked()),this,SLOT(slots_shiftCancel()));
}

void Widget_Count::initLastData()
{
	m_LastData.m_AllCount = pMainFrm->m_sRunningInfo.m_checkedNum;
	m_LastData.m_FailCount = pMainFrm->m_sRunningInfo.m_failureNumFromIOcard;
	for (int i=1;i<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;i++)
	{
		m_LastData.m_CameraTypeCount[i] = pMainFrm->m_sRunningInfo.m_iErrorTypeCount[i];
	}
	for (int i=1;i<=pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		for(int j=1;j<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;j++)
		{
			m_LastData.m_TypeCount[i][j] = pMainFrm->m_sRunningInfo.m_cErrorTypeInfo[i-1].iErrorCountByType[j];
		}
	}
}

void Widget_Count::upDateListInfo()
{
}
bool Widget_Count::slots_intoWidget()
{
	//upDateListInfo();
	return true;
}
bool Widget_Count::leaveWidget()
{
	return true;
}
void Widget_Count::slots_OpenRecord()
{
	QDate dateSelecte = widgetCountSet->ui.calendarWidget->selectedDate();
	// 	QString path = pMainFrm->m_sConfigInfo.m_strAppPath + "CountInfo/" + dateSelecte.year() + "-" + dateSelecte.month() + "-" + dateSelecte.day() + ".txt";
	//QString strFileName = pMainFrm->m_sConfigInfo.m_strAppPath + "CountInfo/" + dateSelecte.toString(Qt::ISODate) + ".txt";
	QString strFileName;
	if(0==widgetCountSet->ui.comboBox->currentIndex())
	{
		strFileName = pMainFrm->m_sConfigInfo.m_strAppPath + "CountInfo/HalfCount/" + dateSelecte.toString(Qt::ISODate) + ".txt";
	}else{
		strFileName = pMainFrm->m_sConfigInfo.m_strAppPath + "CountInfo/AllCount/" + dateSelecte.toString(Qt::ISODate) + ".txt";
	}
	if(!QFile::exists(strFileName))
	{
		QMessageBox::information(this,tr("Information"),tr("No record in select date!"));
		return;
	}

	openInNotePad(strFileName);

	QFile readFile(strFileName);

	if (!readFile.open(QFile::ReadOnly | QIODevice::Text))
	{
		pMainFrm->Logfile.write(tr("Fail in Open Record File " + dateSelecte.toString("Qt::ISODate")), AbnormityLog);
		return;
	}

	QTextStream readStream(&readFile);
	//	QTextStream writeStream(&writeFile);
	while (!readStream.atEnd())
	{
		QString line(readStream.readLine());
	}
	readFile.close();

}
DWORD Widget_Count::GetProcessIdFromName(const char*processName)    
{
	PROCESSENTRY32 pe;
	DWORD id = 0;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if( !Process32First(hSnapshot,&pe) )
		return 0;
	char pname[300];
	do
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if( Process32Next(hSnapshot,&pe)==FALSE )
			break;
		//把WCHAR*类型转换为const char*类型
		sprintf_s(pname,"%ws",pe.szExeFile,260);
		//比较两个字符串，如果找到了要找的进程
		if(strcmp(pname,processName) == 0)
		{
			id = pe.th32ProcessID;
			break;
		}

	} while(1);

	CloseHandle(hSnapshot);

	return id;
}
void Widget_Count::openInNotePad(QString str)
{
	DWORD pid = GetProcessIdFromName("notepad.exe");
	//获取进程的最大权限
	if(pid!=0)
	{
		HANDLE token = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
		//关闭进程
		TerminateProcess(token, 0);
	}
	ShellExecuteA(NULL,"open",(LPCSTR)str.toLocal8Bit(),NULL,NULL,SW_SHOW);
}

void Widget_Count::slots_DeleteRecord()
{
	QDate dateSelecte = widgetCountSet->ui.calendarWidget->selectedDate();
	// 	QString strFileName = QString(pMainFrm->m_sConfigInfo.m_strAppPath + "CountInfo/" + dateSelecte.year() + "-" + dateSelecte.month() + "-" + dateSelecte.day() + ".txt");
	QString strDirPath = pMainFrm->m_sConfigInfo.m_strAppPath + "CountInfo/HalfCount/";
	QString strFileName;
	if(0==widgetCountSet->ui.comboBox->currentIndex())
	{
		strFileName = pMainFrm->m_sConfigInfo.m_strAppPath + "CountInfo/HalfCount/" + dateSelecte.toString(Qt::ISODate) + ".txt";
	}else{
		strFileName = pMainFrm->m_sConfigInfo.m_strAppPath + "CountInfo/AllCount/" + dateSelecte.toString(Qt::ISODate) + ".txt";
	}
	if(!QFile::exists(strFileName))
	{
		QMessageBox::information(this,tr("Information"),tr("No record in select date!"));
	}
	QDir dir(strDirPath);
	if (!dir.remove(strFileName))
	{
		QMessageBox::information(this,tr("Information"),tr("Deleting [%1] fail!").arg(strFileName));
		return;
	}
}

void Widget_Count::SaveToDatabase()
{
	QDateTime dateTime = QDateTime::currentDateTime();
	m_TemporaryData.m_AllCount += pMainFrm->m_sRunningInfo.m_checkedNum - m_LastData.m_AllCount;
	m_TemporaryData.m_FailCount += pMainFrm->m_sRunningInfo.m_failureNumFromIOcard - m_LastData.m_FailCount;
	for (int i=1;i<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;i++)
	{
		m_TemporaryData.m_CameraTypeCount[i] += pMainFrm->m_sRunningInfo.m_iErrorTypeCount[i] - m_LastData.m_CameraTypeCount[i];
	}
	for (int i=1;i<=pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		for(int j=1;j<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;j++)
		{
			m_TemporaryData.m_TypeCount[i][j] += pMainFrm->m_sRunningInfo.m_cErrorTypeInfo[i-1].iErrorCountByType[j] - m_LastData.m_TypeCount[i][j];
		}
	}
	//所有缺陷总数 小于 剔废总数 不合格数取缺陷总数
	int sum=0;
	for (int i=1;i<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;i++)
	{
		sum += m_TemporaryData.m_CameraTypeCount[i];
	}
	m_TemporaryData.m_FailCount  = sum < m_TemporaryData.m_FailCount ? sum : m_TemporaryData.m_FailCount;
	m_WidgetReport->m_database->insert(dateTime.toString("yyMMddhhmmss"),m_TemporaryData);
	m_TemporaryData.TemporaryDataClear();
}
void Widget_Count::SaveDataToharddisk()
{
	m_LastData.m_AllCount =  pMainFrm->m_sRunningInfo.m_checkedNum ;
	m_LastData.m_FailCount = pMainFrm->m_sRunningInfo.m_failureNumFromIOcard;
	for (int i=1;i<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;i++)
	{
		m_LastData.m_CameraTypeCount[i] = pMainFrm->m_sRunningInfo.m_iErrorTypeCount[i];
	}
	for (int i=1;i<=pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		for(int j=1;j<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;j++)
		{
			m_LastData.m_TypeCount[i][j] = pMainFrm->m_sRunningInfo.m_cErrorTypeInfo[i-1].iErrorCountByType[j];
		}
	}
	QSettings LoadLastData(pMainFrm->m_sConfigInfo.m_strDataPath,QSettings::IniFormat);
	LoadLastData.setIniCodec(QTextCodec::codecForName("GBK"));
	QString strSession;
	strSession = QString("LastTimeDate/Checknumber");
	LoadLastData.setValue(strSession,m_LastData.m_AllCount);
	strSession = QString("LastTimeDate/Failurenumber");
	LoadLastData.setValue(strSession,m_LastData.m_FailCount);
	strSession = QString("LastTimeDate/NCamCount");
	LoadLastData.setValue(strSession,pMainFrm->NCamCount);

	for (int i=1;i<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;i++)
	{
		strSession = QString("LastTimeDate/ErrorType_%1_count").arg(i);
		LoadLastData.setValue(strSession,m_LastData.m_CameraTypeCount[i]);
	}
	for (int i=1;i<=pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		for(int j=1;j<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;j++)
		{
			strSession = QString("LastTimeDate/Camera%1_ErrorType%2").arg(i).arg(j);
			LoadLastData.setValue(strSession,m_LastData.m_TypeCount[i][j]);
			strSession = QString("LastTimeDate/Camera%1_LastImgErrorType%2").arg(i).arg(j);
			LoadLastData.setValue(strSession,pMainFrm->m_sErrorInfo.i_countErrorType[i][j]);
		}
	}
}
bool Widget_Count::slots_SaveCountInfo()
{
	pMainFrm->Logfile.write(tr("SaveCountInfo!"),OperationLog,0);
	bool bIsEmptyFile = false;
	QString strFileName;
	strFileName = pMainFrm->m_sConfigInfo.m_strAppPath + "CountInfo/HalfCount/";
	QDir *temp = new QDir;
	bool exist = temp->exists(strFileName);
	if(!exist)
	{
		bool ok = temp->mkdir(strFileName);
	}

	bool ret = false;
	QDate date = QDate::currentDate();
	strFileName = strFileName +	date.toString(Qt::ISODate) + ".txt";
	if(!QFile::exists(strFileName))
	{
		QFile createFile(strFileName);
		if(!createFile.open(QFile::WriteOnly | QIODevice::Text))
		{
			pMainFrm->Logfile.write(tr("Create Count File Failure!"),OperationLog,0);
			return ret;
		}
		bIsEmptyFile = true;
		createFile.close();
	}
	QFile readFile(strFileName);
	if (!readFile.open(QFile::Append | QIODevice::Text))
	{
		ret = false;
		pMainFrm->Logfile.write(tr("Read Count File Failure!"),OperationLog,0);
		return ret;
	}
	QFile writeFile(strFileName);
	//读入流和写入流
	//写入流文件在最后才WriteOnly打开
	QTextStream writeStream(&writeFile);
	if(true)
	{
		if (!bIsEmptyFile)
		{
			writeStream<<"\n";

		}

		QTime time = QTime::currentTime();
		writeStream<<QString(tr("Time:  %1:%2:%3")).arg(time.hour()).arg(time.minute()).arg(time.second())<<"\t";	//保存数据时间
		writeStream<<QString(tr("Product Number:  %1")).arg(pMainFrm->m_sRunningInfo.m_checkedNum)<<"\t";			//检测总数
		writeStream<<QString(tr("Reject Number:  %1")).arg(pMainFrm->m_sRunningInfo.m_failureNumFromIOcard)<<"\t";//不合格数 从IO卡反馈
		double dFailurRate=0.0;
		if (0 != pMainFrm->m_sRunningInfo.m_checkedNum)
		{
			dFailurRate = 1.0*pMainFrm->m_sRunningInfo.m_failureNumFromIOcard/pMainFrm->m_sRunningInfo.m_checkedNum*100;//不合格率
		}
		writeStream<<QString(tr("Reject Rate:  %1%")).arg(dFailurRate)<<"\n";
		writeStream<<tr("Count:")<<"\t";
		for(int i=1;i<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;i++)
		{
			if(pMainFrm->m_sRunningInfo.m_iErrorTypeCount[i]!=0)
			{
				writeStream<<pMainFrm->m_sErrorInfo.m_vstrErrorType.at(i) + ":" + QString::number(pMainFrm->m_sRunningInfo.m_iErrorTypeCount[i])<<"\t\t";
			}
		}
		writeStream<<"\n";
		writeStream<<"\t";
		for (int i = 1;i<=pMainFrm->NCamCount;i++)
		{
			if (i<10)
			{
				writeStream<<tr("the 0%1 time").arg(i)<<"\t\t\t\t";
			}
			else
			{
				writeStream<<tr("the %1 time").arg(i)<<"\t\t\t\t";
			}
		}
		writeStream<<"\n";

		for (int i = 1;i<=pMainFrm->m_sSystemInfo.iCamCount;i++)
		{
			if (i<10)
			{
				writeStream<<tr("Camera0%1").arg(i)<<"\t";
			}
			else
			{
				writeStream<<tr("Camera%1").arg(i)<<"\t";
			}
			for(int j=1;j<=pMainFrm->NCamCount;j++)
			{
				int errorName = pMainFrm->m_sErrorInfo.i_countErrorType[i][j];
				if(errorName!=0)
				{
					QString tempString = pMainFrm->m_sErrorInfo.m_vstrErrorType.at(errorName);
					tempString += "/";
					int errorLastName = m_lasterrorData[i][j];
					if(errorLastName!=0)
					{
						tempString += pMainFrm->m_sErrorInfo.m_vstrErrorType.at(errorLastName);
					}
					ChangeQString(tempString);
					writeStream<<tempString<<"\t";
					ret = true;
				}else{
					QString tempString = "/";
					int errorLastName = m_lasterrorData[i][j];
					if(errorLastName!=0)
					{
						tempString += pMainFrm->m_sErrorInfo.m_vstrErrorType.at(errorLastName);
					}
					ChangeQString(tempString);
					writeStream<<tempString<<"\t";
				}
				m_lasterrorData[i][j] = errorName;
			}
			writeStream<<"\n";
		}
		writeStream<<"\n";
	}
	if (!writeFile.open(QFile::Append | QIODevice::Text))
	{
		ret = false;
		pMainFrm->Logfile.write(tr("Write Count File Failure!"),OperationLog,0);
		return ret;
	}
	writeStream.flush();//写入流到文件

	writeFile.close();
	delete temp;
	if(ret)
	{
		SaveToDatabase();
	}
	SaveDataToharddisk();
	return ret;
}
bool Widget_Count::ChangeQString(QString& tempString)
{
	int tt = tempString.length();
	while(tempString.length()<24)
	{
		tempString+=" ";
		if(tt <8)
		{
			if(tempString.length() == 24)
			{
				break;
			}
		}else{
			if(tempString.length() == 16)
			{
				break;
			}
		}
	}
	return true;
}
void Widget_Count::slots_timerClearCountInfo()
{
	QTime time = QTime::currentTime();
	int iTime = time.hour()*10000+time.minute()*100+time.second();
	int iShift[3];
	iShift[0] = shift1.hour()*10000 + shift1.minute()*100 + shift1.second();
	iShift[1] = shift2.hour()*10000 + shift2.minute()*100 + shift2.second();
	iShift[2] = shift3.hour()*10000 + shift3.minute()*100 + shift3.second();

	for (int i = 0; i<2; i++)
	{
		if (iShift[i] > iShift[i+1])
		{
			int temp = iShift[i];
			iShift[i] = iShift[i+1];
			iShift[i+1] = temp;
		}
	}
	if (iTime>=iShift[0] && iTime<iShift[1])
	{
		if (!isClear1)
		{
			ClearAllData();
			isClear1 = true;
			isClear2 = false;
			isClear3 = false;
		}
	}
	if (iTime>=iShift[1] && iTime<iShift[2])
	{
		if (!isClear2)
		{
			ClearAllData();
			isClear1 = false;
			isClear2 = true;
			isClear3 = false;
		}
	}	
	if (iTime<iShift[0] || iTime>=iShift[2])
	{
		if (!isClear3)
		{
			ClearAllData();
			isClear1 = false;
			isClear2 = false;
			isClear3 = true;
		}
	}
}
void Widget_Count::slots_saveRecordOK()
{
}
void Widget_Count::slots_saveRecordCancel()
{
}
void Widget_Count::slots_shiftOK()
{
	
}
void Widget_Count::slots_shiftCancel()
{

}
void Widget_Count::ClearAllData(int resultFromQ)
{
	pMainFrm->Logfile.write(tr("Set zero!"),OperationLog);
	pMainFrm->m_sRunningInfo.m_mutexRunningInfo.lock();
	//手动清零，保存历史数据,后续插入数据库
 	m_WidgetReport->clearReport();
	m_TemporaryData.TemporaryDataClear();
	m_LastData.TemporaryDataClear();
	QSettings LoadLastData(pMainFrm->m_sConfigInfo.m_strDataPath,QSettings::IniFormat);
	LoadLastData.setIniCodec(QTextCodec::codecForName("GBK"));
	QString strSession;
	strSession = QString("LastTimeDate/Checknumber");
	LoadLastData.setValue(strSession,0);
	strSession = QString("LastTimeDate/Failurenumber");
	LoadLastData.setValue(strSession,0);
	for (int i=1;i<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;i++)
	{
		strSession = QString("LastTimeDate/ErrorType_%1_count").arg(i);
		LoadLastData.setValue(strSession,0);
	}
	for (int i=1;i<=pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		for(int j=1;j<=pMainFrm->m_sErrorInfo.m_iErrorTypeCount;j++)
		{
			strSession = QString("LastTimeDate/Camera%1_ErrorType%2").arg(i).arg(j);
			LoadLastData.setValue(strSession,0);
			strSession = QString("LastTimeDate/Camera%1_LastImgErrorType%2").arg(i).arg(j);
			LoadLastData.setValue(strSession,0);
			pMainFrm->m_sErrorInfo.i_countErrorType[i][j] = 0;
			m_lasterrorData[i][j]=0;
		}
	}
	
	pMainFrm->m_sRunningInfo.m_checkedNum = 0;
	pMainFrm->m_sRunningInfo.m_passNum = 0;
	pMainFrm->m_sRunningInfo.m_failureNum = 0;
	pMainFrm->m_sRunningInfo.m_passNum2 = 0;
	pMainFrm->m_sRunningInfo.m_failureNum2 = 0;

	pMainFrm->m_sRunningInfo.m_failureNumFromIOcard = 0;
	pMainFrm->m_sRunningInfo.nModelCheckedCount = 0;

	for (int i=0;i<CAMERA_MAX_COUNT;i++)
	{
		pMainFrm->m_sRunningInfo.m_iErrorCamCount[i] = 0;
		pMainFrm->m_sRunningInfo.m_cErrorTypeInfo[i].Clear();
	}
	for (int i=0;i<ERRORTYPE_MAX_COUNT;i++)
	{
		pMainFrm->m_sRunningInfo.m_iErrorTypeCount[i] = 0;
	}
	pMainFrm->widget_carveSetting->errorList_widget->slots_clearTable();
	pMainFrm->m_sRunningInfo.m_mutexRunningInfo.unlock();
}