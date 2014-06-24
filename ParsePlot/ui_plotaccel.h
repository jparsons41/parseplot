/********************************************************************************
** Form generated from reading UI file 'plotaccel.ui'
**
** Created: Tue Jun 24 10:51:35 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTACCEL_H
#define UI_PLOTACCEL_H

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

class Ui_PlotAccel
{
public:
    QDialogButtonBox *buttonBox;
    QCustomPlot *plot;
    QRadioButton *scaleOnlyY;
    QPushButton *printButton;
    QRadioButton *scaleBoth;
    QRadioButton *scaleOnlyX;
    QPushButton *savPDF;

    void setupUi(QDialog *PlotAccel)
    {
        if (PlotAccel->objectName().isEmpty())
            PlotAccel->setObjectName(QString::fromUtf8("PlotAccel"));
        PlotAccel->setWindowModality(Qt::WindowModal);
        PlotAccel->resize(930, 671);
        buttonBox = new QDialogButtonBox(PlotAccel);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(560, 610, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        plot = new QCustomPlot(PlotAccel);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(10, 10, 901, 591));
        scaleOnlyY = new QRadioButton(PlotAccel);
        scaleOnlyY->setObjectName(QString::fromUtf8("scaleOnlyY"));
        scaleOnlyY->setGeometry(QRect(240, 630, 101, 17));
        printButton = new QPushButton(PlotAccel);
        printButton->setObjectName(QString::fromUtf8("printButton"));
        printButton->setGeometry(QRect(440, 620, 75, 23));
        scaleBoth = new QRadioButton(PlotAccel);
        scaleBoth->setObjectName(QString::fromUtf8("scaleBoth"));
        scaleBoth->setGeometry(QRect(130, 630, 101, 17));
        scaleBoth->setChecked(true);
        scaleOnlyX = new QRadioButton(PlotAccel);
        scaleOnlyX->setObjectName(QString::fromUtf8("scaleOnlyX"));
        scaleOnlyX->setGeometry(QRect(20, 630, 101, 17));
        savPDF = new QPushButton(PlotAccel);
        savPDF->setObjectName(QString::fromUtf8("savPDF"));
        savPDF->setGeometry(QRect(360, 620, 75, 23));

        retranslateUi(PlotAccel);
        QObject::connect(buttonBox, SIGNAL(accepted()), PlotAccel, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PlotAccel, SLOT(reject()));

        QMetaObject::connectSlotsByName(PlotAccel);
    } // setupUi

    void retranslateUi(QDialog *PlotAccel)
    {
        PlotAccel->setWindowTitle(QApplication::translate("PlotAccel", "Dialog", 0, QApplication::UnicodeUTF8));
        scaleOnlyY->setText(QApplication::translate("PlotAccel", "Scale Y Only", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("PlotAccel", "Print", 0, QApplication::UnicodeUTF8));
        scaleBoth->setText(QApplication::translate("PlotAccel", "Scale X & Y", 0, QApplication::UnicodeUTF8));
        scaleOnlyX->setText(QApplication::translate("PlotAccel", "Scale X Only", 0, QApplication::UnicodeUTF8));
        savPDF->setText(QApplication::translate("PlotAccel", "Save PDF", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlotAccel: public Ui_PlotAccel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTACCEL_H
