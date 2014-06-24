/********************************************************************************
** Form generated from reading UI file 'plotdata.ui'
**
** Created: Tue Jun 24 10:51:35 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTDATA_H
#define UI_PLOTDATA_H

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

class Ui_PlotData
{
public:
    QDialogButtonBox *buttonBox;
    QCustomPlot *plot;
    QRadioButton *scaleOnlyY;
    QRadioButton *scaleBoth;
    QRadioButton *scaleOnlyX;
    QPushButton *savPDF;
    QPushButton *printButton;

    void setupUi(QDialog *PlotData)
    {
        if (PlotData->objectName().isEmpty())
            PlotData->setObjectName(QString::fromUtf8("PlotData"));
        PlotData->setWindowModality(Qt::WindowModal);
        PlotData->resize(931, 647);
        buttonBox = new QDialogButtonBox(PlotData);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(570, 610, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        plot = new QCustomPlot(PlotData);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(10, 10, 901, 591));
        scaleOnlyY = new QRadioButton(PlotData);
        scaleOnlyY->setObjectName(QString::fromUtf8("scaleOnlyY"));
        scaleOnlyY->setGeometry(QRect(260, 620, 101, 17));
        scaleBoth = new QRadioButton(PlotData);
        scaleBoth->setObjectName(QString::fromUtf8("scaleBoth"));
        scaleBoth->setGeometry(QRect(130, 620, 101, 17));
        scaleBoth->setChecked(true);
        scaleOnlyX = new QRadioButton(PlotData);
        scaleOnlyX->setObjectName(QString::fromUtf8("scaleOnlyX"));
        scaleOnlyX->setGeometry(QRect(30, 620, 101, 17));
        savPDF = new QPushButton(PlotData);
        savPDF->setObjectName(QString::fromUtf8("savPDF"));
        savPDF->setGeometry(QRect(370, 610, 75, 23));
        printButton = new QPushButton(PlotData);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setGeometry(QRect(450, 610, 75, 23));

        retranslateUi(PlotData);
        QObject::connect(buttonBox, SIGNAL(accepted()), PlotData, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PlotData, SLOT(reject()));

        QMetaObject::connectSlotsByName(PlotData);
    } // setupUi

    void retranslateUi(QDialog *PlotData)
    {
        PlotData->setWindowTitle(QApplication::translate("PlotData", "ParsePlot", 0, QApplication::UnicodeUTF8));
        scaleOnlyY->setText(QApplication::translate("PlotData", "Scale Y Only", 0, QApplication::UnicodeUTF8));
        scaleBoth->setText(QApplication::translate("PlotData", "Scale X & Y", 0, QApplication::UnicodeUTF8));
        scaleOnlyX->setText(QApplication::translate("PlotData", "Scale X Only", 0, QApplication::UnicodeUTF8));
        savPDF->setText(QApplication::translate("PlotData", "Save PDF", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("PlotData", "Print", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlotData: public Ui_PlotData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTDATA_H
