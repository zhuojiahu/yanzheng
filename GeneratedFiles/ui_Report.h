/********************************************************************************
** Form generated from reading UI file 'Report.ui'
**
** Created: Wed Jul 20 09:15:19 2022
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORT_H
#define UI_REPORT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <dhbasewidget.h>

QT_BEGIN_NAMESPACE

class Ui_widget_Report
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_report;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_4;
    QCalendarWidget *calendarWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_check;
    QSpacerItem *horizontalSpacer_2;
    DHBaseWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_pie;

    void setupUi(QWidget *widget_Report)
    {
        if (widget_Report->objectName().isEmpty())
            widget_Report->setObjectName(QString::fromUtf8("widget_Report"));
        widget_Report->resize(1307, 861);
        verticalLayout_3 = new QVBoxLayout(widget_Report);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_report = new QWidget(widget_Report);
        widget_report->setObjectName(QString::fromUtf8("widget_report"));
        verticalLayout = new QVBoxLayout(widget_report);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(widget_report);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QFont font;
        font.setPointSize(10);
        tableView->setFont(font);
        tableView->horizontalHeader()->setDefaultSectionSize(120);

        verticalLayout->addWidget(tableView);


        verticalLayout_3->addWidget(widget_report);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, 5, -1);
        widget_2 = new QWidget(widget_Report);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(600, 0));
        widget_2->setMaximumSize(QSize(600, 16777215));
        verticalLayout_4 = new QVBoxLayout(widget_2);
        verticalLayout_4->setSpacing(5);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 5);
        calendarWidget = new QCalendarWidget(widget_2);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(15);
        calendarWidget->setFont(font1);
        calendarWidget->setStyleSheet(QString::fromUtf8("\n"
"QToolButton#qt_calendar_monthbutton,#qt_calendar_yearbutton{\n"
"\n"
"color: #9ea5a9; \n"
"\n"
"font: 15pt simHei; \n"
"}\n"
"\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar\n"
"{\n"
"\n"
"background-color: #2F2F3E;\n"
"}\n"
"QCalendarWidget QToolButton {\n"
"    height: 60px;\n"
"    width: 150px;\n"
"    color: white;\n"
"    font-size: 24px;\n"
"    icon-size: 56px, 56px;\n"
"}\n"
"QCalendarWidget QMenu {\n"
"    width: 150px;\n"
"    left: 20px;\n"
"    color: white;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
""));
        calendarWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        verticalLayout_4->addWidget(calendarWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_check = new QPushButton(widget_2);
        pushButton_check->setObjectName(QString::fromUtf8("pushButton_check"));
        pushButton_check->setMinimumSize(QSize(200, 0));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton_check->setFont(font2);

        horizontalLayout_2->addWidget(pushButton_check);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(widget_2);

        widget = new DHBaseWidget(widget_Report);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 25, 0, 0);
        widget_pie = new QWidget(widget);
        widget_pie->setObjectName(QString::fromUtf8("widget_pie"));
        QFont font3;
        font3.setPointSize(9);
        widget_pie->setFont(font3);

        horizontalLayout_3->addWidget(widget_pie);


        horizontalLayout->addWidget(widget);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 8);

        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(widget_Report);

        QMetaObject::connectSlotsByName(widget_Report);
    } // setupUi

    void retranslateUi(QWidget *widget_Report)
    {
        widget_Report->setWindowTitle(QApplication::translate("widget_Report", "Form", 0, QApplication::UnicodeUTF8));
        pushButton_check->setText(QApplication::translate("widget_Report", "SHOW", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class widget_Report: public Ui_widget_Report {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORT_H
