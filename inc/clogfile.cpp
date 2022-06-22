#include "clogfile.h"
#include <QDate>
#include <QSettings>
#include <QApplication>
#include "reviewer.h"
extern Reviewer *pMainFrm;

QString GetCurrentAppPath()
{
	QString AppPath;
	//��ΪQt��UNICODE��GetModuXXX��һ��������ҪLPWSTR����
	TCHAR tcStr[MAX_PATH];
	//_splitpath��һ��������ҪLPCSTR����
	char cStr[MAX_PATH];
	char drive[MAX_PATH], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	GetModuleFileName(NULL, tcStr, sizeof(tcStr));
	//��Ҫ�ѿ��ֽ�tcStrת��Ϊ���ֽ�cStr
	int iLength ;  	
	iLength = WideCharToMultiByte(CP_ACP, 0, tcStr, -1, NULL, 0, NULL, NULL); 	
	WideCharToMultiByte(CP_ACP, 0, tcStr, -1, cStr, iLength, NULL, NULL); 
	//���
	_splitpath_s(cStr, drive, dir, fname, ext);
	strcat_s(drive, dir);
	//���ֽ���ת��ΪUNICODE�����Ͽɷ�ֹ����·������
	AppPath = QString::fromLocal8Bit(drive);	
	return AppPath;
}


WriteLogThread::WriteLogThread(QObject *parent)
	: QThread(parent)
{

}
WriteLogThread::WriteLogThread()
	: QThread()
{
}

WriteLogThread::~WriteLogThread()
{

}
void WriteLogThread::run()
{
	m_bStopThread = false;
	while(!m_bStopThread)
	{
		if (listLog.size()>0)
		{
			mutexLog.lock();
			s_LogInfo sLogInfo = listLog.takeFirst();
			mutexLog.unlock();
			write(sLogInfo.strInfo,sLogInfo.logtype,sLogInfo.showInferface);
		}
		Sleep(1);
	}
}
void WriteLogThread::StartThread()
{
	m_bStopThread = false;
	start();
}
void WriteLogThread::StopThread()
{
	m_bStopThread = true;
}
void WriteLogThread::WaitThreadStop()
{
	if (isRunning())
	{
		if (!m_bStopThread)
		{
			m_bStopThread = true;
		}
		wait();
	}
}

void WriteLogThread::Initpath(e_SaveLogType logtype)
{
	QString apppath;// = m_widget.GetCurrentAppPath();
	switch(logtype)
	{
	case OperationLog:
		m_strlogfilepath = apppath + "LogFiles/OperationLog/";
		m_strLogInfo = "OperationInfo";
		break;
	case CheckLog:
		m_strlogfilepath = apppath + "LogFiles/CheckLog/";
		m_strLogInfo = "CheckInfo";
		break;
	case MendParamLog:
		m_strlogfilepath = apppath + "LogFiles/MendParamLog/";
		m_strLogInfo = "MendParamInfo";
		break;
	case AbnormityLog:
		m_strlogfilepath = apppath + "LogFiles/AbnormityLog/";		
		m_strLogInfo = "AbnormityInfo";
		break;
	case StatInfo:
		m_strlogfilepath = apppath + "LogFiles/StatInfo/";		
		m_strLogInfo = "StatInfo";
		break;
	case AlgorithmDLL:
		m_strlogfilepath = apppath + "LogFiles/AlgorithmDLL/";
		m_strLogInfo = "AlgorithmInfo";
		break;
	default:
		m_strlogfilepath = apppath + "LogFiles/OtherLog/";
		m_strLogInfo = "OtherInfo";
		break;
	}
}

void WriteLogThread::write(QString strInfo,e_SaveLogType logtype, int showInferface)
{
	if (logtype == AbnormityLog)
	{
		showInferface = 0;
	}
	mutexLog.lock();
	if ((0 == showInferface)||(1 == showInferface))
	{
		// 	mutxLogFile.lock();
		QDate date = QDate::currentDate();
		QTime time = QTime::currentTime();

		Initpath(logtype);

		QString strFilePath = m_strlogfilepath +
			QString("%1-%2-%3.txt").arg(date.year()).arg(date.month()).arg(date.day());

		QDir *tempDir = new QDir;
		bool exist = true;
		int i = 0;
		QString strLastFilePath;
		strLastFilePath = strFilePath;
		exist = tempDir->exists(strFilePath);
		while(exist)
		{
			exist = tempDir->exists(strFilePath);

			if (exist)
			{
				strLastFilePath = strFilePath;
				strFilePath = m_strlogfilepath + \
					QString("%1-%2-%3_%4.txt").arg(date.year()).arg(date.month()).arg(date.day()).arg(++i);
			}
		}
		delete tempDir;
		tempDir = NULL;

		strFilePath = strLastFilePath;
		QSettings errorSet(strFilePath,QSettings::IniFormat);
		errorSet.setIniCodec("GBK");
		errorSet.beginGroup("setup");
		int nTotalNum = errorSet.value("total",0).toInt();

		if (nTotalNum > 1000)
		{
			nTotalNum = 1;
			strFilePath = m_strlogfilepath + \
				QString("%1-%2-%3_%4.txt").arg(date.year()).arg(date.month()).arg(date.day()).arg(i);

			QSettings errorSet(strFilePath,QSettings::IniFormat);
			errorSet.setIniCodec("GBK");
			errorSet.beginGroup("setup");
			//			int nTotalNum = errorSet.value("total",0).toInt();
			nTotalNum = ++nTotalNum;

			errorSet.endGroup();
			errorSet.beginGroup(m_strLogInfo);
			QString errorData = QString("%1-%2-%3 %4:%5:%6 "+strInfo).arg(date.year()).arg(date.month()).\
				arg(date.day()).arg(time.hour()).arg(time.minute()).arg(time.second());
			errorSet.setValue(QString("INFO_%1").arg(nTotalNum),errorData);
			errorSet.endGroup();
			errorSet.beginGroup("setup");
			errorSet.setValue("total",QString::number(nTotalNum));
			errorSet.endGroup();	

		}
		else
		{
			nTotalNum = ++nTotalNum;
			errorSet.endGroup();
			errorSet.beginGroup(m_strLogInfo);
			QString errorData = QString("%1-%2-%3 %4:%5:%6 "+strInfo).arg(date.year()).arg(date.month()).\
				arg(date.day()).arg(time.hour()).arg(time.minute()).arg(time.second());
			errorSet.setValue(QString("INFO_%1").arg(nTotalNum),errorData);
			errorSet.endGroup();
			errorSet.beginGroup("setup");
			errorSet.setValue("total",QString::number(nTotalNum));
			errorSet.endGroup();	
		}
		// 	mutxLogFile.unlock();
		//���䣺���ں�ʱ������ǰ�油0������
	}
	mutexLog.unlock();
}




CLogFile::CLogFile()
{
	pThreadWriteLog = new WriteLogThread();
	pThreadWriteLog->StartThread();

}

CLogFile::~CLogFile()
{
	pThreadWriteLog->StopThread();
	pThreadWriteLog->WaitThreadStop();
	delete pThreadWriteLog;
}

void CLogFile::write(QString strInfo,e_SaveLogType logtype, int showInferface)
{
	s_LogInfo sLogInfo;
	sLogInfo.strInfo = strInfo;
	sLogInfo.logtype = logtype;
	sLogInfo.showInferface = showInferface;
	pThreadWriteLog->mutexLog.lock();
	pThreadWriteLog->listLog.append(sLogInfo);
	pThreadWriteLog->mutexLog.unlock();
}

