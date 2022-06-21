#ifndef CMYERRORLIST_H
#define CMYERRORLIST_H

#include <QWidget>
#include "stateTool.h"
class CMyErrorList 
{
public:
	CMyErrorList();
	~CMyErrorList();
	void initErrorList(int nWidth,int nHeight,int nBitCount,int nBlockCount,bool bAllocMemeroy=true);
	void releaseElement();
	QMutex m_mutexmErrorList;
	QList<CGrabElement *> listError;
private:
	QVector<QRgb> vColorTable;
};

#endif // CMYERRORLIST_H
