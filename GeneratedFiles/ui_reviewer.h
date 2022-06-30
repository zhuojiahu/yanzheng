/********************************************************************************
** Form generated from reading UI file 'reviewer.ui'
**
** Created: Fri Jun 24 17:22:39 2022
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVIEWER_H
#define UI_REVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReviewerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QMainWindow *ReviewerClass)
    {
        if (ReviewerClass->objectName().isEmpty())
            ReviewerClass->setObjectName(QString::fromUtf8("ReviewerClass"));
        ReviewerClass->resize(600, 400);
        centralWidget = new QWidget(ReviewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);

        ReviewerClass->setCentralWidget(centralWidget);

        retranslateUi(ReviewerClass);

        QMetaObject::connectSlotsByName(ReviewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ReviewerClass)
    {
        ReviewerClass->setWindowTitle(QApplication::translate("ReviewerClass", "Reviewer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ReviewerClass: public Ui_ReviewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVIEWER_H
