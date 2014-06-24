/********************************************************************************
** Form generated from reading UI file 'plotdigdata.ui'
**
** Created: Tue Jun 24 10:51:35 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTDIGDATA_H
#define UI_PLOTDIGDATA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_PlotDigData
{
public:
    QPushButton *printButton;
    QCustomPlot *plot;
    QRadioButton *scaleBoth;
    QRadioButton *scaleOnlyX;
    QDialogButtonBox *buttonBox;
    QRadioButton *scaleOnlyY;
    QPushButton *savPDF;

    void setupUi(QDialog *PlotDigData)
    {
        if (PlotDigData->objectName().isEmpty())
            PlotDigData->setObjectName(QString::fromUtf8("PlotDigData"));
        PlotDigData->setWindowModality(Qt::WindowModal);
        PlotDigData->resize(1058, 714);
        printButton = new QPushButton(PlotDigData);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setGeometry(QRect(480, 640, 75, 23));
        plot = new QCustomPlot(PlotDigData);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(40, 40, 901, 591));
        scaleBoth = new QRadioButton(PlotDigData);
        scaleBoth->setObjectName(QString::fromUtf8("scaleBoth"));
        scaleBoth->setGeometry(QRect(160, 650, 101, 17));
        scaleBoth->setChecked(true);
        scaleOnlyX = new QRadioButton(PlotDigData);
        scaleOnlyX->setObjectName(QString::fromUtf8("scaleOnlyX"));
        scaleOnlyX->setGeometry(QRect(60, 650, 101, 17));
        buttonBox = new QDialogButtonBox(PlotDigData);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(600, 640, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        scaleOnlyY = new QRadioButton(PlotDigData);
        scaleOnlyY->setObjectName(QString::fromUtf8("scaleOnlyY"));
        scaleOnlyY->setGeometry(QRect(290, 650, 101, 17));
        savPDF = new QPushButton(PlotDigData);
        savPDF->setObjectName(QString::fromUtf8("savPDF"));
        savPDF->setGeometry(QRect(400, 640, 75, 23));

        retranslateUi(PlotDigData);

        QMetaObject::connectSlotsByName(PlotDigData);
    } // setupUi

    void retranslateUi(QDialog *PlotDigData)
    {
        PlotDigData->setWindowTitle(QApplication::translate("PlotDigData", "Dialog", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("PlotDigData", "Print", 0, QApplication::UnicodeUTF8));
        scaleBoth->setText(QApplication::translate("PlotDigData", "Scale X & Y", 0, QApplication::UnicodeUTF8));
        scaleOnlyX->setText(QApplication::translate("PlotDigData", "Scale X Only", 0, QApplication::UnicodeUTF8));
        scaleOnlyY->setText(QApplication::translate("PlotDigData", "Scale Y Only", 0, QApplication::UnicodeUTF8));
        savPDF->setText(QApplication::translate("PlotDigData", "Save PDF", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlotDigData: public Ui_PlotDigData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTDIGDATA_H
