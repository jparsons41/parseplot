/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jun 24 10:51:35 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTreeView *treeView;
    QLabel *label;
    QLabel *label_3;
    QPushButton *setDefaultPath;
    QLabel *defaultFilePath;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_5;
    QLabel *fileExtension;
    QLabel *label_6;
    QLabel *location;
    QLabel *label_7;
    QLabel *sensorName;
    QLabel *label_8;
    QLabel *numberOfChannels;
    QLabel *label_9;
    QLabel *fileLength;
    QLabel *label_11;
    QLabel *sampleFrequency;
    QProgressBar *progressBar_input;
    QPushButton *pushButton_2;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QPushButton *WriteData;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *SensorComboBox;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLabel *label_12;
    QLabel *label_10;
    QLabel *label_13;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *m_pLabelPressCal1;
    QLineEdit *m_pLabelPressCal2;
    QLineEdit *m_pLabelAccelCal1;
    QLineEdit *m_pLabelAccelCal2;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(840, 649);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 10, 441, 561));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(560, 260, 251, 21));
        label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(480, 260, 81, 21));
        setDefaultPath = new QPushButton(centralWidget);
        setDefaultPath->setObjectName(QString::fromUtf8("setDefaultPath"));
        setDefaultPath->setGeometry(QRect(480, 200, 91, 23));
        defaultFilePath = new QLabel(centralWidget);
        defaultFilePath->setObjectName(QString::fromUtf8("defaultFilePath"));
        defaultFilePath->setGeometry(QRect(600, 200, 211, 20));
        defaultFilePath->setFrameShape(QFrame::Panel);
        defaultFilePath->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(480, 50, 331, 141));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        fileExtension = new QLabel(layoutWidget);
        fileExtension->setObjectName(QString::fromUtf8("fileExtension"));
        fileExtension->setFrameShape(QFrame::Panel);
        fileExtension->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(0, QFormLayout::FieldRole, fileExtension);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        location = new QLabel(layoutWidget);
        location->setObjectName(QString::fromUtf8("location"));
        location->setFrameShape(QFrame::Panel);
        location->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(1, QFormLayout::FieldRole, location);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_7);

        sensorName = new QLabel(layoutWidget);
        sensorName->setObjectName(QString::fromUtf8("sensorName"));
        sensorName->setFrameShape(QFrame::Panel);
        sensorName->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(2, QFormLayout::FieldRole, sensorName);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_8);

        numberOfChannels = new QLabel(layoutWidget);
        numberOfChannels->setObjectName(QString::fromUtf8("numberOfChannels"));
        numberOfChannels->setFrameShape(QFrame::Panel);
        numberOfChannels->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(3, QFormLayout::FieldRole, numberOfChannels);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_9);

        fileLength = new QLabel(layoutWidget);
        fileLength->setObjectName(QString::fromUtf8("fileLength"));
        fileLength->setFrameShape(QFrame::Panel);
        fileLength->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(4, QFormLayout::FieldRole, fileLength);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_11);

        sampleFrequency = new QLabel(layoutWidget);
        sampleFrequency->setObjectName(QString::fromUtf8("sampleFrequency"));
        sampleFrequency->setFrameShape(QFrame::Panel);
        sampleFrequency->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(5, QFormLayout::FieldRole, sampleFrequency);

        progressBar_input = new QProgressBar(centralWidget);
        progressBar_input->setObjectName(QString::fromUtf8("progressBar_input"));
        progressBar_input->setGeometry(QRect(480, 230, 331, 23));
        progressBar_input->setValue(0);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(580, 430, 111, 23));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(460, 460, 359, 23));
        progressBar->setValue(0);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(460, 518, 359, 23));
        WriteData = new QPushButton(centralWidget);
        WriteData->setObjectName(QString::fromUtf8("WriteData"));
        WriteData->setGeometry(QRect(460, 489, 359, 23));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(470, 330, 71, 16));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(460, 390, 91, 16));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(620, 290, 121, 20));
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(480, 20, 331, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        SensorComboBox = new QComboBox(layoutWidget1);
        SensorComboBox->setObjectName(QString::fromUtf8("SensorComboBox"));

        horizontalLayout->addWidget(SensorComboBox);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(550, 310, 121, 111));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout->addWidget(label_12);

        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout->addWidget(label_10);

        label_13 = new QLabel(layoutWidget2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        verticalLayout->addWidget(label_13);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(680, 310, 127, 112));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_pLabelPressCal1 = new QLineEdit(layoutWidget3);
        m_pLabelPressCal1->setObjectName(QString::fromUtf8("m_pLabelPressCal1"));

        verticalLayout_2->addWidget(m_pLabelPressCal1);

        m_pLabelPressCal2 = new QLineEdit(layoutWidget3);
        m_pLabelPressCal2->setObjectName(QString::fromUtf8("m_pLabelPressCal2"));

        verticalLayout_2->addWidget(m_pLabelPressCal2);

        m_pLabelAccelCal1 = new QLineEdit(layoutWidget3);
        m_pLabelAccelCal1->setObjectName(QString::fromUtf8("m_pLabelAccelCal1"));

        verticalLayout_2->addWidget(m_pLabelAccelCal1);

        m_pLabelAccelCal2 = new QLineEdit(layoutWidget3);
        m_pLabelAccelCal2->setObjectName(QString::fromUtf8("m_pLabelAccelCal2"));

        verticalLayout_2->addWidget(m_pLabelAccelCal2);

        layoutWidget4 = new QWidget(centralWidget);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(460, 547, 361, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget4);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        treeView->raise();
        label->raise();
        label_3->raise();
        setDefaultPath->raise();
        defaultFilePath->raise();
        layoutWidget->raise();
        progressBar_input->raise();
        pushButton_2->raise();
        progressBar->raise();
        pushButton->raise();
        WriteData->raise();
        label_14->raise();
        label_15->raise();
        label_16->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 840, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ParsePlot v0.1", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "INPUT FILE:", 0, QApplication::UnicodeUTF8));
        setDefaultPath->setText(QApplication::translate("MainWindow", "Set File Path", 0, QApplication::UnicodeUTF8));
        defaultFilePath->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "File Extension", 0, QApplication::UnicodeUTF8));
        fileExtension->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Location", 0, QApplication::UnicodeUTF8));
        location->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Sensor Name", 0, QApplication::UnicodeUTF8));
        sensorName->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Number of Channels", 0, QApplication::UnicodeUTF8));
        numberOfChannels->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "File Length (secs)", 0, QApplication::UnicodeUTF8));
        fileLength->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Sample Frequency (Hz)", 0, QApplication::UnicodeUTF8));
        sampleFrequency->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Save Cal Levels", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Plot Data", 0, QApplication::UnicodeUTF8));
        WriteData->setText(QApplication::translate("MainWindow", "Write Data To File", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Pressure", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Acceleration", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "Calibration Levels", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Sensor Type", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Chan A(mV/Pascal)", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Chan B(mV/Pascal)", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Chan A(mV/G)", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Chan B(mV/G)", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "Plot Pressure ", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainWindow", "Plot Acceleration", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
