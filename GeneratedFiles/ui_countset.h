/********************************************************************************
** Form generated from reading UI file 'countset.ui'
**
** Created: Fri Jun 24 17:22:41 2022
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTSET_H
#define UI_COUNTSET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "dhbasewidget.h"

QT_BEGIN_NAMESPACE

class Ui_CountSet
{
public:
    QVBoxLayout *verticalLayout_2;
    DHBaseWidget *widget_calendar;
    QGridLayout *gridLayout;
    QPushButton *pushButton_deleteRecord;
    QCalendarWidget *calendarWidget;
    QHBoxLayout *Layout_calendarTitle;
    QComboBox *comboBox;
    QPushButton *pushButton_openRecord;
    DHBaseWidget *widget_saveRecord;
    QGridLayout *gridLayout_saveRecord;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_saveRecordOK;
    QPushButton *pushButton_saveRecordCancel;
    QRadioButton *radioButton_30minite;
    QHBoxLayout *Layout_saveRecordTitle;
    QCheckBox *checkBox_saveRecord;
    QRadioButton *radioButton_60minite;
    DHBaseWidget *widget_shitf;
    QVBoxLayout *verticalLayout_shitf;
    QHBoxLayout *Layout_shiftTitle;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QTimeEdit *timeEdit_shift1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QTimeEdit *timeEdit_shift2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QTimeEdit *timeEdit_shift3;
    QCheckBox *checkBox_AutoSetZero;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_shiftOK;
    QPushButton *pushButton_shiftCancel;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *CountSet)
    {
        if (CountSet->objectName().isEmpty())
            CountSet->setObjectName(QString::fromUtf8("CountSet"));
        CountSet->resize(330, 784);
        CountSet->setMinimumSize(QSize(300, 0));
        CountSet->setMaximumSize(QSize(330, 16777215));
        verticalLayout_2 = new QVBoxLayout(CountSet);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_calendar = new DHBaseWidget(CountSet);
        widget_calendar->setObjectName(QString::fromUtf8("widget_calendar"));
        QFont font;
        font.setPointSize(12);
        widget_calendar->setFont(font);
        gridLayout = new QGridLayout(widget_calendar);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        pushButton_deleteRecord = new QPushButton(widget_calendar);
        pushButton_deleteRecord->setObjectName(QString::fromUtf8("pushButton_deleteRecord"));
        pushButton_deleteRecord->setMinimumSize(QSize(100, 40));
        pushButton_deleteRecord->setMaximumSize(QSize(80, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        pushButton_deleteRecord->setFont(font1);

        gridLayout->addWidget(pushButton_deleteRecord, 2, 2, 1, 1);

        calendarWidget = new QCalendarWidget(widget_calendar);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setMaximumSize(QSize(16777215, 16777215));
        calendarWidget->setFont(font);
        calendarWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(calendarWidget, 1, 0, 1, 3);

        Layout_calendarTitle = new QHBoxLayout();
        Layout_calendarTitle->setObjectName(QString::fromUtf8("Layout_calendarTitle"));

        gridLayout->addLayout(Layout_calendarTitle, 0, 0, 1, 3);

        comboBox = new QComboBox(widget_calendar);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(100, 38));
        comboBox->setMaximumSize(QSize(80, 38));

        gridLayout->addWidget(comboBox, 2, 0, 1, 1);

        pushButton_openRecord = new QPushButton(widget_calendar);
        pushButton_openRecord->setObjectName(QString::fromUtf8("pushButton_openRecord"));
        sizePolicy.setHeightForWidth(pushButton_openRecord->sizePolicy().hasHeightForWidth());
        pushButton_openRecord->setSizePolicy(sizePolicy);
        pushButton_openRecord->setMinimumSize(QSize(100, 40));
        pushButton_openRecord->setMaximumSize(QSize(80, 40));
        pushButton_openRecord->setFont(font1);

        gridLayout->addWidget(pushButton_openRecord, 2, 1, 1, 1);


        verticalLayout_2->addWidget(widget_calendar);

        widget_saveRecord = new DHBaseWidget(CountSet);
        widget_saveRecord->setObjectName(QString::fromUtf8("widget_saveRecord"));
        widget_saveRecord->setFont(font);
        gridLayout_saveRecord = new QGridLayout(widget_saveRecord);
        gridLayout_saveRecord->setObjectName(QString::fromUtf8("gridLayout_saveRecord"));
        gridLayout_saveRecord->setContentsMargins(-1, 0, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_saveRecordOK = new QPushButton(widget_saveRecord);
        pushButton_saveRecordOK->setObjectName(QString::fromUtf8("pushButton_saveRecordOK"));
        pushButton_saveRecordOK->setMinimumSize(QSize(120, 40));
        pushButton_saveRecordOK->setMaximumSize(QSize(120, 40));
        pushButton_saveRecordOK->setFont(font);

        horizontalLayout_2->addWidget(pushButton_saveRecordOK);

        pushButton_saveRecordCancel = new QPushButton(widget_saveRecord);
        pushButton_saveRecordCancel->setObjectName(QString::fromUtf8("pushButton_saveRecordCancel"));
        pushButton_saveRecordCancel->setMinimumSize(QSize(120, 40));
        pushButton_saveRecordCancel->setMaximumSize(QSize(120, 40));
        pushButton_saveRecordCancel->setFont(font);

        horizontalLayout_2->addWidget(pushButton_saveRecordCancel);


        gridLayout_saveRecord->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        radioButton_30minite = new QRadioButton(widget_saveRecord);
        radioButton_30minite->setObjectName(QString::fromUtf8("radioButton_30minite"));
        radioButton_30minite->setFont(font);

        gridLayout_saveRecord->addWidget(radioButton_30minite, 2, 0, 1, 1);

        Layout_saveRecordTitle = new QHBoxLayout();
        Layout_saveRecordTitle->setObjectName(QString::fromUtf8("Layout_saveRecordTitle"));

        gridLayout_saveRecord->addLayout(Layout_saveRecordTitle, 0, 0, 1, 1);

        checkBox_saveRecord = new QCheckBox(widget_saveRecord);
        checkBox_saveRecord->setObjectName(QString::fromUtf8("checkBox_saveRecord"));
        checkBox_saveRecord->setFont(font);

        gridLayout_saveRecord->addWidget(checkBox_saveRecord, 1, 0, 1, 1);

        radioButton_60minite = new QRadioButton(widget_saveRecord);
        radioButton_60minite->setObjectName(QString::fromUtf8("radioButton_60minite"));
        radioButton_60minite->setFont(font);

        gridLayout_saveRecord->addWidget(radioButton_60minite, 3, 0, 1, 1);


        verticalLayout_2->addWidget(widget_saveRecord);

        widget_shitf = new DHBaseWidget(CountSet);
        widget_shitf->setObjectName(QString::fromUtf8("widget_shitf"));
        widget_shitf->setFont(font);
        verticalLayout_shitf = new QVBoxLayout(widget_shitf);
        verticalLayout_shitf->setObjectName(QString::fromUtf8("verticalLayout_shitf"));
        verticalLayout_shitf->setContentsMargins(-1, 0, -1, -1);
        Layout_shiftTitle = new QHBoxLayout();
        Layout_shiftTitle->setObjectName(QString::fromUtf8("Layout_shiftTitle"));

        verticalLayout_shitf->addLayout(Layout_shiftTitle);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(widget_shitf);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_4->addWidget(label, 0, Qt::AlignHCenter);

        timeEdit_shift1 = new QTimeEdit(widget_shitf);
        timeEdit_shift1->setObjectName(QString::fromUtf8("timeEdit_shift1"));
        timeEdit_shift1->setFont(font);

        horizontalLayout_4->addWidget(timeEdit_shift1);


        verticalLayout_shitf->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(widget_shitf);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_5->addWidget(label_2, 0, Qt::AlignHCenter);

        timeEdit_shift2 = new QTimeEdit(widget_shitf);
        timeEdit_shift2->setObjectName(QString::fromUtf8("timeEdit_shift2"));
        timeEdit_shift2->setFont(font);

        horizontalLayout_5->addWidget(timeEdit_shift2);


        verticalLayout_shitf->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(widget_shitf);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_6->addWidget(label_3, 0, Qt::AlignHCenter);

        timeEdit_shift3 = new QTimeEdit(widget_shitf);
        timeEdit_shift3->setObjectName(QString::fromUtf8("timeEdit_shift3"));
        timeEdit_shift3->setFont(font);

        horizontalLayout_6->addWidget(timeEdit_shift3);


        verticalLayout_shitf->addLayout(horizontalLayout_6);

        checkBox_AutoSetZero = new QCheckBox(widget_shitf);
        checkBox_AutoSetZero->setObjectName(QString::fromUtf8("checkBox_AutoSetZero"));
        checkBox_AutoSetZero->setFont(font);

        verticalLayout_shitf->addWidget(checkBox_AutoSetZero);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_shiftOK = new QPushButton(widget_shitf);
        pushButton_shiftOK->setObjectName(QString::fromUtf8("pushButton_shiftOK"));
        pushButton_shiftOK->setMinimumSize(QSize(120, 40));
        pushButton_shiftOK->setMaximumSize(QSize(120, 40));
        pushButton_shiftOK->setFont(font);

        horizontalLayout_3->addWidget(pushButton_shiftOK);

        pushButton_shiftCancel = new QPushButton(widget_shitf);
        pushButton_shiftCancel->setObjectName(QString::fromUtf8("pushButton_shiftCancel"));
        pushButton_shiftCancel->setMinimumSize(QSize(120, 40));
        pushButton_shiftCancel->setMaximumSize(QSize(120, 40));
        pushButton_shiftCancel->setFont(font);

        horizontalLayout_3->addWidget(pushButton_shiftCancel);


        verticalLayout_shitf->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(widget_shitf);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(CountSet);

        QMetaObject::connectSlotsByName(CountSet);
    } // setupUi

    void retranslateUi(QWidget *CountSet)
    {
        CountSet->setWindowTitle(QApplication::translate("CountSet", "Form", 0, QApplication::UnicodeUTF8));
        pushButton_deleteRecord->setText(QApplication::translate("CountSet", "Delete record", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("CountSet", "TimeQuery", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CountSet", "ShiftQuery", 0, QApplication::UnicodeUTF8)
        );
        pushButton_openRecord->setText(QApplication::translate("CountSet", "Open record", 0, QApplication::UnicodeUTF8));
        pushButton_saveRecordOK->setText(QApplication::translate("CountSet", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_saveRecordCancel->setText(QApplication::translate("CountSet", "Cancel", 0, QApplication::UnicodeUTF8));
        radioButton_30minite->setText(QApplication::translate("CountSet", "Save record every 30minite", 0, QApplication::UnicodeUTF8));
        checkBox_saveRecord->setText(QApplication::translate("CountSet", "Save Record", 0, QApplication::UnicodeUTF8));
        radioButton_60minite->setText(QApplication::translate("CountSet", "Save record every 60minite", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CountSet", "Shift1:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CountSet", "Shift2:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CountSet", "Shift3:", 0, QApplication::UnicodeUTF8));
        checkBox_AutoSetZero->setText(QApplication::translate("CountSet", "AutoSetZero", 0, QApplication::UnicodeUTF8));
        pushButton_shiftOK->setText(QApplication::translate("CountSet", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_shiftCancel->setText(QApplication::translate("CountSet", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CountSet: public Ui_CountSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTSET_H
