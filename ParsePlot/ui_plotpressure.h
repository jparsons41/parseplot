/********************************************************************************
** Form generated from reading UI file 'plotpressure.ui'
**
** Created: Tue Feb 3 14:33:03 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTPRESSURE_H
#define UI_PLOTPRESSURE_H

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

class Ui_PlotPressure
{
public:
    QDialogButtonBox *buttonBox;
    QCustomPlot *plot;
    QRadioButton *scaleBoth;
    QPushButton *savPDF;
    QRadioButton *scaleOnlyY;
    QPushButton *printButton;
    QRadioButton *scaleOnlyX;

    void setupUi(QDialog *PlotPressure)
    {
        if (PlotPressure->objectName().isEmpty())
            PlotPressure->setObjectName(QString::fromUtf8("PlotPressure"));
        PlotPressure->setWindowModality(Qt::WindowModal);
        PlotPressure->resize(956, 678);
        buttonBox = new QDialogButtonBox(PlotPressure);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(600, 630, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        plot = new QCustomPlot(PlotPressure);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(20, 10, 901, 591));
        scaleBoth = new QRadioButton(PlotPressure);
        scaleBoth->setObjectName(QString::fromUtf8("scaleBoth"));
        scaleBoth->setGeometry(QRect(150, 640, 101, 17));
        scaleBoth->setChecked(true);
        savPDF = new QPushButton(PlotPressure);
        savPDF->setObjectName(QString::fromUtf8("savPDF"));
        savPDF->setGeometry(QRect(390, 630, 75, 23));
        scaleOnlyY = new QRadioButton(PlotPressure);
        scaleOnlyY->setObjectName(QString::fromUtf8("scaleOnlyY"));
        scaleOnlyY->setGeometry(QRect(240, 640, 101, 17));
        printButton = new QPushButton(PlotPressure);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setGeometry(QRect(470, 630, 75, 23));
        scaleOnlyX = new QRadioButton(PlotPressure);
        scaleOnlyX->setObjectName(QString::fromUtf8("scaleOnlyX"));
        scaleOnlyX->setGeometry(QRect(50, 640, 101, 17));

        retranslateUi(PlotPressure);
        QObject::connect(buttonBox, SIGNAL(accepted()), PlotPressure, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PlotPressure, SLOT(reject()));

        QMetaObject::connectSlotsByName(PlotPressure);
    } // setupUi

    void retranslateUi(QDialog *PlotPressure)
    {
        PlotPressure->setWindowTitle(QApplication::translate("PlotPressure", "Dialog", 0, QApplication::UnicodeUTF8));
        scaleBoth->setText(QApplication::translate("PlotPressure", "Scale X & Y", 0, QApplication::UnicodeUTF8));
        savPDF->setText(QApplication::translate("PlotPressure", "Save PDF", 0, QApplication::UnicodeUTF8));
        scaleOnlyY->setText(QApplication::translate("PlotPressure", "Scale Y Only", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("PlotPressure", "Print", 0, QApplication::UnicodeUTF8));
        scaleOnlyX->setText(QApplication::translate("PlotPressure", "Scale X Only", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlotPressure: public Ui_PlotPressure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTPRESSURE_H
