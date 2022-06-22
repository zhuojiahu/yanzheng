/********************************************************************************
** Form generated from reading UI file 'Widget_CountPlot.ui'
**
** Created: Tue Jun 21 16:59:46 2022
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_COUNTPLOT_H
#define UI_WIDGET_COUNTPLOT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <dhbasewidget.h>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_Widget_CountPlot
{
public:
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *CustomPlot;
    QHBoxLayout *horizontalLayout;
    DHBaseWidget *widget_ShiftSet;
    QGridLayout *gridLayout;
    QPushButton *pushButton_Cancel;
    QLabel *label_3;
    QTimeEdit *timeEdit_2;
    QTimeEdit *timeEdit_3;
    QLabel *label_2;
    QPushButton *pushButton_Save;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioBtn_Half;
    QRadioButton *radioBtn_anHour;
    QLabel *label_1;
    QTimeEdit *timeEdit_1;
    QCalendarWidget *calendarWidget;
    QVBoxLayout *verticalLayout;
    DHBaseWidget *widget_shift;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_Shift1;
    QRadioButton *radioButton_Shift2;
    QRadioButton *radioButton_Shift3;
    QRadioButton *radioButton_ShiftAll;
    DHBaseWidget *widget_table;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *radioButton_table1;
    QRadioButton *radioButton_table2;
    QRadioButton *radioButton_table3;
    QPushButton *pushButton_Search;
    DHBaseWidget *widget_pie;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_2;

    void setupUi(QWidget *Widget_CountPlot)
    {
        if (Widget_CountPlot->objectName().isEmpty())
            Widget_CountPlot->setObjectName(QString::fromUtf8("Widget_CountPlot"));
        Widget_CountPlot->resize(1024, 768);
        Widget_CountPlot->setContextMenuPolicy(Qt::CustomContextMenu);
        verticalLayout_3 = new QVBoxLayout(Widget_CountPlot);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        CustomPlot = new QCustomPlot(Widget_CountPlot);
        CustomPlot->setObjectName(QString::fromUtf8("CustomPlot"));
        CustomPlot->setContextMenuPolicy(Qt::CustomContextMenu);
        CustomPlot->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(CustomPlot);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        widget_ShiftSet = new DHBaseWidget(Widget_CountPlot);
        widget_ShiftSet->setObjectName(QString::fromUtf8("widget_ShiftSet"));
        widget_ShiftSet->setContextMenuPolicy(Qt::NoContextMenu);
        gridLayout = new QGridLayout(widget_ShiftSet);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(12);
        gridLayout->setContentsMargins(-1, 25, -1, -1);
        pushButton_Cancel = new QPushButton(widget_ShiftSet);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pushButton_Cancel->setFont(font);

        gridLayout->addWidget(pushButton_Cancel, 5, 1, 1, 1);

        label_3 = new QLabel(widget_ShiftSet);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        timeEdit_2 = new QTimeEdit(widget_ShiftSet);
        timeEdit_2->setObjectName(QString::fromUtf8("timeEdit_2"));
        timeEdit_2->setMinimumSize(QSize(0, 25));
        timeEdit_2->setMaximumTime(QTime(23, 59, 59));
        timeEdit_2->setMinimumTime(QTime(0, 0, 0));

        gridLayout->addWidget(timeEdit_2, 2, 1, 1, 1);

        timeEdit_3 = new QTimeEdit(widget_ShiftSet);
        timeEdit_3->setObjectName(QString::fromUtf8("timeEdit_3"));
        timeEdit_3->setMinimumSize(QSize(0, 25));
        timeEdit_3->setMaximumTime(QTime(23, 59, 59));
        timeEdit_3->setMinimumTime(QTime(0, 0, 0));

        gridLayout->addWidget(timeEdit_3, 3, 1, 1, 1);

        label_2 = new QLabel(widget_ShiftSet);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        pushButton_Save = new QPushButton(widget_ShiftSet);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        pushButton_Save->setMinimumSize(QSize(0, 40));
        pushButton_Save->setFont(font);

        gridLayout->addWidget(pushButton_Save, 5, 0, 1, 1);

        groupBox = new QGroupBox(widget_ShiftSet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 50));
        groupBox->setContextMenuPolicy(Qt::NoContextMenu);
        groupBox->setStyleSheet(QString::fromUtf8("border-color: rgb(190, 190, 190);"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioBtn_Half = new QRadioButton(groupBox);
        radioBtn_Half->setObjectName(QString::fromUtf8("radioBtn_Half"));

        horizontalLayout_2->addWidget(radioBtn_Half);

        radioBtn_anHour = new QRadioButton(groupBox);
        radioBtn_anHour->setObjectName(QString::fromUtf8("radioBtn_anHour"));

        horizontalLayout_2->addWidget(radioBtn_anHour);


        gridLayout->addWidget(groupBox, 4, 0, 1, 2);

        label_1 = new QLabel(widget_ShiftSet);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        timeEdit_1 = new QTimeEdit(widget_ShiftSet);
        timeEdit_1->setObjectName(QString::fromUtf8("timeEdit_1"));
        timeEdit_1->setMinimumSize(QSize(0, 25));
        timeEdit_1->setTime(QTime(8, 0, 0));
        timeEdit_1->setMaximumTime(QTime(23, 59, 59));

        gridLayout->addWidget(timeEdit_1, 0, 1, 1, 1);

        gridLayout->setRowStretch(0, 1);

        horizontalLayout->addWidget(widget_ShiftSet);

        calendarWidget = new QCalendarWidget(Widget_CountPlot);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setContextMenuPolicy(Qt::NoContextMenu);
        calendarWidget->setStyleSheet(QString::fromUtf8("\n"
"QToolButton#qt_calendar_monthbutton,#qt_calendar_yearbutton{\n"
"\n"
"color: #9ea5a9; \n"
"\n"
"font: 13pt simHei; \n"
"}\n"
"\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar\n"
"{\n"
"\n"
"background-color: #2F2F3E;\n"
"}\n"
"QCalendarWidget QToolButton {\n"
"    height: 40px;\n"
"    width: 100px;\n"
"    color: white;\n"
"    font-size: 24px;\n"
"    icon-size: 48px, 48px;\n"
"}\n"
"QCalendarWidget QMenu {\n"
"    width: 100px;\n"
"    left: 20px;\n"
"    color: white;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
""));
        calendarWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout->addWidget(calendarWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, 0);
        widget_shift = new DHBaseWidget(Widget_CountPlot);
        widget_shift->setObjectName(QString::fromUtf8("widget_shift"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_shift->sizePolicy().hasHeightForWidth());
        widget_shift->setSizePolicy(sizePolicy);
        widget_shift->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout_2 = new QVBoxLayout(widget_shift);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 25, -1, 5);
        radioButton_Shift1 = new QRadioButton(widget_shift);
        radioButton_Shift1->setObjectName(QString::fromUtf8("radioButton_Shift1"));
        radioButton_Shift1->setChecked(true);

        verticalLayout_2->addWidget(radioButton_Shift1);

        radioButton_Shift2 = new QRadioButton(widget_shift);
        radioButton_Shift2->setObjectName(QString::fromUtf8("radioButton_Shift2"));

        verticalLayout_2->addWidget(radioButton_Shift2);

        radioButton_Shift3 = new QRadioButton(widget_shift);
        radioButton_Shift3->setObjectName(QString::fromUtf8("radioButton_Shift3"));

        verticalLayout_2->addWidget(radioButton_Shift3);

        radioButton_ShiftAll = new QRadioButton(widget_shift);
        radioButton_ShiftAll->setObjectName(QString::fromUtf8("radioButton_ShiftAll"));

        verticalLayout_2->addWidget(radioButton_ShiftAll);


        verticalLayout->addWidget(widget_shift);

        widget_table = new DHBaseWidget(Widget_CountPlot);
        widget_table->setObjectName(QString::fromUtf8("widget_table"));
        widget_table->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout_4 = new QVBoxLayout(widget_table);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, 15, -1, -1);
        radioButton_table1 = new QRadioButton(widget_table);
        radioButton_table1->setObjectName(QString::fromUtf8("radioButton_table1"));
        radioButton_table1->setChecked(true);

        verticalLayout_4->addWidget(radioButton_table1);

        radioButton_table2 = new QRadioButton(widget_table);
        radioButton_table2->setObjectName(QString::fromUtf8("radioButton_table2"));

        verticalLayout_4->addWidget(radioButton_table2);

        radioButton_table3 = new QRadioButton(widget_table);
        radioButton_table3->setObjectName(QString::fromUtf8("radioButton_table3"));

        verticalLayout_4->addWidget(radioButton_table3);


        verticalLayout->addWidget(widget_table);

        pushButton_Search = new QPushButton(Widget_CountPlot);
        pushButton_Search->setObjectName(QString::fromUtf8("pushButton_Search"));
        pushButton_Search->setMinimumSize(QSize(150, 50));
        pushButton_Search->setFont(font);

        verticalLayout->addWidget(pushButton_Search);


        horizontalLayout->addLayout(verticalLayout);

        widget_pie = new DHBaseWidget(Widget_CountPlot);
        widget_pie->setObjectName(QString::fromUtf8("widget_pie"));
        verticalLayout_5 = new QVBoxLayout(widget_pie);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 30, 0, 0);
        widget_2 = new QWidget(widget_pie);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));

        verticalLayout_5->addWidget(widget_2);


        horizontalLayout->addWidget(widget_pie);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 5);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 7);

        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout_3->setStretch(0, 5);
        verticalLayout_3->setStretch(1, 3);

        retranslateUi(Widget_CountPlot);

        QMetaObject::connectSlotsByName(Widget_CountPlot);
    } // setupUi

    void retranslateUi(QWidget *Widget_CountPlot)
    {
        Widget_CountPlot->setWindowTitle(QApplication::translate("Widget_CountPlot", "CountPlot", 0, QApplication::UnicodeUTF8));
        pushButton_Cancel->setText(QApplication::translate("Widget_CountPlot", "Cancel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget_CountPlot", "Shift3 StartTime:", 0, QApplication::UnicodeUTF8));
        timeEdit_2->setDisplayFormat(QApplication::translate("Widget_CountPlot", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        timeEdit_3->setDisplayFormat(QApplication::translate("Widget_CountPlot", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget_CountPlot", "Shift2 StartTime:", 0, QApplication::UnicodeUTF8));
        pushButton_Save->setText(QApplication::translate("Widget_CountPlot", "Save", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        radioBtn_Half->setText(QApplication::translate("Widget_CountPlot", "Half an Hour", 0, QApplication::UnicodeUTF8));
        radioBtn_anHour->setText(QApplication::translate("Widget_CountPlot", "an Hour", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("Widget_CountPlot", "Shift1 StartTime:", 0, QApplication::UnicodeUTF8));
        timeEdit_1->setDisplayFormat(QApplication::translate("Widget_CountPlot", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        radioButton_Shift1->setText(QApplication::translate("Widget_CountPlot", "Shift 1", 0, QApplication::UnicodeUTF8));
        radioButton_Shift2->setText(QApplication::translate("Widget_CountPlot", "shift 2", 0, QApplication::UnicodeUTF8));
        radioButton_Shift3->setText(QApplication::translate("Widget_CountPlot", "shift 3", 0, QApplication::UnicodeUTF8));
        radioButton_ShiftAll->setText(QApplication::translate("Widget_CountPlot", "All shift", 0, QApplication::UnicodeUTF8));
        radioButton_table1->setText(QApplication::translate("Widget_CountPlot", "Failure Number table", 0, QApplication::UnicodeUTF8));
        radioButton_table2->setText(QApplication::translate("Widget_CountPlot", "Failure Rate table", 0, QApplication::UnicodeUTF8));
        radioButton_table3->setText(QApplication::translate("Widget_CountPlot", "Shift Defect Count Plot", 0, QApplication::UnicodeUTF8));
        pushButton_Search->setText(QApplication::translate("Widget_CountPlot", "Search", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget_CountPlot: public Ui_Widget_CountPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_COUNTPLOT_H
