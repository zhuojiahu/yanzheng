#ifndef DATABASE_H
#define DATABASE_H
#include "qsqldatabase.h"
#include "qsqlquery.h"
#include "qsqldriver.h"
#include "qsqlrecord.h"
struct TemporaryData{
	long long id[50];
	int m_CameraTypeCount[50]; //ĳ��ȱ�ݵ��߷�����
	int m_AllCount; //��ǰ������Ŀ
	int m_FailCount; //��ǰ�߷���Ŀ
	int m_Type[50]; //��������
	int m_TypeCount[40][50]; //ÿ�������Ӧ��һ��ȱ���߷���
	void TemporaryDataClear()
	{
		memset(this,0,sizeof(TemporaryData));
	}
};
struct SeleteData{
	long long id;
	int m_CameraTypeCount; //ĳ��ȱ�ݵ��߷�����
	int m_AllCount; //��ǰ������Ŀ
	int m_FailCount; //��ǰ�߷���Ŀ
	int m_Type; //��������
	int m_TypeCount[40]; //ÿ�������Ӧ��һ��ȱ���߷���
	void SeleteDatClear()
	{
		memset(this,0,sizeof(SeleteData));
	}
};
class DataBase
{
public:
	DataBase(int);

	enum QueryFlags{
		ByHalfanHour = 0 ,
		ByanHour
	};

public:
	bool createConnection();  //����һ������
	bool createTable();       //�������ݿ��
	bool insert(QString,TemporaryData);            //��������
	QList<SeleteData> queryAll(QString id);          //��ѯһ��������Ϣ
	QList<SeleteData> queryAllByOrder(QString id);          //��ѯһ��������Ϣ ����
	QList<SeleteData> queryAll(QString startTime,QString endTime);          //��ѯ������Ϣ
	QList<SeleteData> queryOnce(QString id);          //��ѯһ�μ�¼����
	bool updateById(int id);  //����
	bool deleteById(int id);  //ɾ��
	bool deleteFromDate(QString dateId);  //ɾ��ָ������֮ǰ�����ݼ�¼
	QList<SeleteData> sortById(QString);          //����
	TemporaryData m_MyData;
public:
	int cameraCount;
};
#endif