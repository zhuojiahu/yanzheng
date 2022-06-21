#include "widget_Report.h"
#include <QDebug>
#include "reviewer.h"
extern Reviewer *pMainFrm;
WidgetReport::WidgetReport(QWidget *parent,int temp)
	: QWidget(parent),m_CameraCount(temp)
{
	ui.setupUi(this);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);	
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows); 
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection); 
	ui.tableView->verticalHeader()->setVisible(false);	
	ui.widget->setWidgetName(tr("Hourly Defect Count Plot"));

	ui.calendarWidget->setLocale(QLocale::Chinese);
	

	QToolButton *prevBtn=ui.calendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_prevmonth"));
	QToolButton *nextBtn=ui.calendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_nextmonth"));
	prevBtn->setIcon(QIcon(":/calendar/prev"));
	nextBtn->setIcon(QIcon(":/calendar/next"));

	m_modelCount = new QStandardItemModel(this);
	ui.tableView->setModel(m_modelCount);
	QStringList headerList;
	headerList<<tr("DateTime");
	headerList<<tr("AllCheck");
	headerList<<tr("AllReject");
	headerList<<tr("Reject Rate");
	for (int i = 1;i <= m_CameraCount;i++)
	{
		headerList <<QObject::tr("Camera%1").arg(i);
	}
	m_modelCount->setHorizontalHeaderLabels(headerList);

	pieImage = new PieView();
	pieImage->setSize(350);
	pieImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	pieImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	model = new QStandardItemModel(10, 2, this);
	model->setHeaderData(0, Qt::Horizontal, tr("Error1"));
	model->setHeaderData(1, Qt::Horizontal, tr("Error2"));
	model->setHeaderData(2, Qt::Horizontal, tr("Error3"));
	model->setHeaderData(3, Qt::Horizontal, tr("Error4"));
	model->setHeaderData(4, Qt::Horizontal, tr("Error5"));
	model->setHeaderData(5, Qt::Horizontal, tr("Error6"));
	model->setHeaderData(6, Qt::Horizontal, tr("Error7"));
	model->setHeaderData(7, Qt::Horizontal, tr("Error8"));
	model->setHeaderData(8, Qt::Horizontal, tr("Error9"));
	model->setHeaderData(9, Qt::Horizontal, tr("Error10"));
	pieImage->setModel(model);
	m_pielayout = new QVBoxLayout(this);
	m_pielayout->addWidget(pieImage);
	m_pielayout->setMargin(4);
	ui.widget_pie->setLayout(m_pielayout);
	m_database = new DataBase(m_CameraCount);
	//删除三个月以前的数据
	QDate m_CurrentDate=QDate::currentDate();
	QDate m_LastDate=m_CurrentDate.addMonths(-6);
	QString dateStr = m_LastDate.toString(Qt::ISODate);
	dateStr.replace("-", "");
	m_database->deleteFromDate(dateStr);

	//测试代码
	connect(ui.tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slots_ShowPie(QModelIndex)));
	connect(ui.pushButton_check,SIGNAL(clicked()),this,SLOT(slots_check()));
	connect(ui.Btn_Export,SIGNAL(clicked()),this,SLOT(slots_Export()));
	memset(&m_temp,0,sizeof(TemporaryData));
}
void WidgetReport::slots_check()
{
	QDate dateSelecte = ui.calendarWidget->selectedDate();
	QString temp = dateSelecte.toString(Qt::ISODate);
	temp.replace("-", "");
	QList<SeleteData> m_temp = m_database->queryAll(temp);
	//TemporaryData m_temp = m_database-> queryAll(temp);
	insertReport(temp,m_temp);
	m_lastTime = temp;
	m_lastDataCount = m_temp.count();
}


void WidgetReport::slots_Export()
{
	QMessageBox::information(NULL, QString::fromLocal8Bit("注意"), QString::fromLocal8Bit("保存excel时间较长请耐心等待约10秒左右"), QMessageBox::Yes, QMessageBox::Yes);
}

void WidgetReport::resizeEvent(QResizeEvent *event)
{
	pieImage->setSize(ui.widget->height() - 30 );
}

void WidgetReport::clearReport()
{
	while(m_modelCount->rowCount()>0 )
	{
		QList<QStandardItem*> listItem = m_modelCount->takeRow(0);
		qDeleteAll(listItem);
		listItem.clear();
	}
}
void WidgetReport::drawPieImage()
{
	int sum=0;
	QColor color[10];
	color[0] = QColor(153,230,0);
	color[1] = QColor(174,77,102);
	color[2] = QColor(128,255,128);
	color[3] = QColor(128,255,255);
	color[4] = QColor(0,128,255);
	color[5] = QColor(255,255,128);
	color[6] = QColor(0,248,128);
	color[7] = QColor(255,0,213);
	color[8] = QColor(35,0,255);
	color[9] = QColor(255,129,0);
	QFont itemFont("微软雅黑",10);
	itemFont.setBold(true);

	model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
	int remp =m_dateList.size();
	for(int i = 0;i < remp;i++)
	{
		sum += m_dateList.at(i).m_Count;
	}
	int m_failCount = m_dateList.at(0).m_failCount;
	m_failCount = sum < m_failCount ? sum : m_failCount;
	int m_AllCount = m_dateList.at(0).m_AllCheckCount;
	if(remp <= 10)
	{
		int t_fail = 0;
		for(int i = 0;i < remp;i++)
		{
			int t_data = 0 ;
			if (i != (remp-1))
			{
				t_data = m_dateList.at(i).m_Count;
// 				if (sum != 0)
// 				{
// 					t_data = m_failCount * t_data  / sum ;
// 				}
				t_fail += t_data;
			}
			else
			{
				t_data = m_failCount - t_fail ;
			}
			model->insertRows(i, 1, QModelIndex());
			model->setData(model->index(i, 0, QModelIndex()), pMainFrm->m_sErrorInfo.m_vstrErrorType.at(m_dateList[i].m_type)+":" 
							+ QString::number(t_data)+"("+QString::number((double)t_data/m_AllCount*100,'f',2)+"%)");
			model->setData(model->index(i, 1, QModelIndex()), QString::number(t_data));
			model->setData(model->index(i, 0, QModelIndex()), color[i], Qt::DecorationRole);
			model->item(i,0)->setFont(itemFont);
		}
	}else{
		int t_fail = 0;
		for(int i = 0;i < 9;i++)
		{
			int t_data = m_dateList.at(i).m_Count;
			if (sum != 0)
			{
				t_data = m_failCount * t_data  / sum ;
			}
			t_fail += t_data;

			model->insertRows(i, 1, QModelIndex());
			model->setData(model->index(i, 0, QModelIndex()), pMainFrm->m_sErrorInfo.m_vstrErrorType.at(m_dateList[i].m_type)+":" 
							+ QString::number(t_data)+"("+QString::number((double)t_data/m_AllCount*100,'f',2)+"%)");
			model->setData(model->index(i, 1, QModelIndex()), QString::number(t_data));
			model->setData(model->index(i, 0, QModelIndex()), color[i], Qt::DecorationRole);
			model->item(i,0)->setFont(itemFont);
		}
		t_fail = m_failCount - t_fail ;
		model->insertRows(9, 1, QModelIndex());
		model->setData(model->index(9, 0, QModelIndex()), tr("Other:") + QString::number(t_fail)+"("+QString::number((double)t_fail/m_AllCount*100,'f',2)+"%)");
		model->setData(model->index(9, 1, QModelIndex()), QString::number(t_fail));
		model->setData(model->index(9, 0, QModelIndex()), color[9], Qt::DecorationRole);
		model->item(9,0)->setFont(itemFont);
	}
}
void WidgetReport::slots_ShowPie(QModelIndex modelIndex)
{
	m_dateList.clear();
	int iListNo = modelIndex.row();
	QModelIndex index = m_modelCount->index(iListNo,0);
	QString name = m_modelCount->data(index).toString();
	QList<SeleteData> m_temp = m_database->sortById(name);
	for(int i = 0; i < m_temp.count();i++)
	{
		TData temp;
		temp.m_type = m_temp[i].m_Type;
		temp.m_Count = m_temp[i].m_CameraTypeCount;
		temp.m_failCount = m_temp[i].m_FailCount;
		temp.m_AllCheckCount = m_temp[i].m_AllCount;
		m_dateList.push_back(temp);
	}
	/*
	TemporaryData m_temp = m_database->sortById(name);
	for(int i = 1; i < 50;i++)
	{
		if(m_temp.m_Type[i] != 0)
		{
			TData temp;
			temp.m_type = m_temp.m_Type[i];
			temp.m_Count = m_temp.m_CameraTypeCount[i];
			m_dateList.push_back(temp);
		}
	}
	*/
	drawPieImage();
}
void WidgetReport::insertReport(QString id,QList<SeleteData> m_datalist)
{
	if(m_lastTime != id || m_lastDataCount != m_datalist.count())
	{
		//清除上一次饼图显示
		model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
		pieImage->update();//刷新
		clearReport();
		m_insertData.clear();
		long long m_lastdataId=0;
		QList<int> m_FailCountList;
		int tmpFailcount=0;
		QList<QList<int>> m_Countlist;//存放相同ID 每个相机检测的缺陷数
		int ps=0;
		QList<QList<int>> m_CameraData; //半个小时 每个相机的检测不合格总数
		for (int i=0;i<m_datalist.count();i++)
		{	
			if (m_lastdataId != m_datalist[i].id )
			{
				if(ps != 0)
				{
					QList<int> m_tempList;
					for(int m=0;m<m_CameraCount;m++)
					{
						int m_tempData=0;
						for (int j=0;j<m_Countlist.count();j++)
						{
							m_tempData += m_Countlist[j][m];
						}
						m_tempList << m_tempData;
					}
					m_CameraData << m_tempList;
					
					m_Countlist.clear();
				}
				ps++;
				m_lastdataId = m_datalist[i].id;
			}

			QList<int> m_Count;
			for(int j=0;j<m_CameraCount;j++)
			{	//保存每一条数据 每一个相机的数据
				m_Count << m_datalist[i].m_TypeCount[j];
			}
			m_Countlist<<m_Count;

			if(i == (m_datalist.count() -1))
			{//最后一组
				QList<int> m_tempList;
				for(int m=0;m<m_CameraCount;m++)
				{
					int m_tempData=0;
					for (int j=0;j<m_Countlist.count();j++)
					{
						m_tempData += m_Countlist[j][m];
					}
					m_tempList << m_tempData;
				}
				m_CameraData << m_tempList;
				m_Countlist.clear();
			}
		}

		m_lastdataId = 0;
		ps=0;
		for (int i=0 ; i<m_datalist.count();i++)
		{
			if (m_lastdataId != m_datalist[i].id )
			{
				if (ps != 0)
				{
					m_FailCountList<<tmpFailcount;
					tmpFailcount = 0;
				}
				else
					ps++;
				tmpFailcount = m_datalist[i].m_CameraTypeCount;
				m_lastdataId = m_datalist[i].id;
			}
			else
			{
				tmpFailcount += m_datalist[i].m_CameraTypeCount;
			}
			if (i == (m_datalist.count()-1))
			{
				m_FailCountList<<tmpFailcount;
			}
			
		}

		int k=0;
		m_lastdataId=0;
		for (int i=0;i<m_datalist.count();i++)
		{	
			if (m_lastdataId != m_datalist[i].id )
			{
				m_insertData.clear();
				m_FailCountList[k] = m_FailCountList[k] < m_datalist[i].m_FailCount ? m_FailCountList[k] : m_datalist[i].m_FailCount;
				QStandardItem* t_temp=new QStandardItem(QString::number(m_datalist[i].id));
				m_insertData<<t_temp;
				t_temp =new QStandardItem(QString::number(m_datalist[i].m_AllCount));
				m_insertData<<t_temp;
				t_temp =new QStandardItem(QString::number(m_FailCountList[k]));
				m_insertData<<t_temp;
				t_temp =new QStandardItem(QString::number((double)m_FailCountList[k]/m_datalist[i].m_AllCount*100,'f',2)+"%");
				m_insertData<<t_temp;
				for(int j=0;j<m_CameraCount;j++)
				{
					t_temp =new QStandardItem(QString::number(m_CameraData[k][j]));
					m_insertData<<t_temp;
				}
				int iRow = m_modelCount->rowCount();
				m_modelCount->insertRow(iRow,m_insertData);

				k++;
				m_lastdataId = m_datalist[i].id;
			}
		}
	}
}
WidgetReport::~WidgetReport()
{

}

