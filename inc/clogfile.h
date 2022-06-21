#ifndef CLOGFILE_H
#define CLOGFILE_H

#include <QString>
#include <QApplication>
#include <QMutex>
#include <QThread>

//#include "common.h"
#include "stateTool.h"
#include "ConfigInfo.h"

struct s_LogInfo
{
	QString strInfo;
	e_SaveLogType logtype;
	int showInferface;
	s_LogInfo()
	{
		strInfo = "";
		logtype = OperationLog;
		showInferface = 0;
	}

};
class WriteLogThread : public QThread
{
	Q_OBJECT

public:
	WriteLogThread(QObject *parent);
	WriteLogThread();
	~WriteLogThread();

	QList<s_LogInfo> listLog;
	QString strLastFilePath;
 	QMutex mutexLog;
private:
	bool m_bStopThread;
// 	QMutex mutxLogFile;
	QString m_strlogfilepath;
	QString m_strLogInfo;

signals:
public slots:
// 	void slots_write();

public:
	// 	s_PLCStatus GetPLCStatus();
	void run();
	void StartThread();
	void StopThread();
	void WaitThreadStop();

	void Initpath(e_SaveLogType logtype);
	void write(QString strInfo,e_SaveLogType logtype, int showInterface = 1);

};

class CLogFile
{
public:
	//enum e_SaveLogType	    //��־����
	//{
	//	OperationLog = 0,			//������־
	//	CheckLog,		            //�����־
	//	MendParamLog,			    //�޸Ĳ�����־
	//	AbnormityLog,               //�쳣��־
	//	StatInfo,					//���ͳ����Ϣ��־
	//	AlgorithmDLL				//�㷨����־
	//};
public:
	CLogFile();
	~CLogFile();

	void write(QString strInfo,e_SaveLogType logtype, int showInterface = 1);
private:
	QMutex mutexWriteLogFile;
// 	static void Initpath(e_SaveLogType logtype);
	QString strLastFilePath;
	WriteLogThread *pThreadWriteLog;
};

#endif // CLOGFILE_H
