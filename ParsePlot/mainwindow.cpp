#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plotdata.h"
#include "plotdigdata.h"
#include "plotpressure.h"
#include "plotaccel.h"

#include <QDebug>
#include <stdio.h>
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QScreen>
#include <QMetaEnum>
#include <QComboBox>
#include <QSettings>


#define swap1long(a) ((((a & 0xff)) << 24) + ((a & 0xff00) << 8) \
        +((a & 0xff0000) >> 8) + (((unsigned)a & 0xff000000u) >> 24))

QSettings settings("HyperionTG", "ParsePlot");
double doublePressCal1 ;
double doublePressCal2 ;
double doubleAccelCal1 ;
double doubleAccelCal2 ;
double accelMax;
double accelMin;
double pressureMax;
double pressureMin;
double channelAMax;
double channelAMin;
double channelBMax;
double channelBMin;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
   // m_pEdit(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    loadSettings();

    QString sensorType =  ui->SensorComboBox->currentText();
//    QObject::connect(ui->SensorComboBox, SIGNAL(currentIndexChanged(int)),


   int getClicked = settings.value("dataFileType").toInt();
   // int getClicked = ui->SensorComboBox->currentIndex();
    switch (getClicked)
    {
//    case RAW_CLICKED:
//        ui->selectRaw->setChecked(true);
//        break;

//    case SYNTRO_OLD_GPS_CLICKED:
//        ui->selectSyntroOldGPS->setChecked(true);
//        break;

//    case IFS5200_CLICKED:
//        ui->IFS5200->setChecked(true);
    }

    ui->progressBar->setRange(0,99);
    ui->progressBar->setValue(0);
    ui->progressBar->show();

    QString sPath = settings.value("defaultFilePath").toString();
    if(sPath.isNull())
        sPath = QString("C:\\");
    dirModel = new QDirModel(this);
    QModelIndex dIndex = dirModel->index(sPath);

    ui->treeView->setModel(dirModel);
    ui->treeView->expand(dIndex);
    ui->treeView->scrollTo(dIndex);
    ui->treeView->setCurrentIndex(dIndex);
    ui->treeView->resizeColumnToContents(0);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(sPath);
    ui->defaultFilePath->setText(sPath);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshDir()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_doubleClicked(QModelIndex index)
{
    int count = 0;
    double SCALE = (2.5/0x7fffff);
    QByteArray fileHeader;
    QByteArray header;
    QByteArray footer;
    QByteArray data;
    QByteArray calib;
    const qint32 *sample;
    int m_plotXSteps;
    m_plotXSteps = 1200000;
    int length;
    length=10;
    static double t;
    t = 0;

    QString SensorSelected = ui->SensorComboBox->currentText();

    if (SensorSelected == "IFS-5200")
    {
         x.clear();
        ui->WriteData->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);


        QDirModel *fModel = new QDirModel(this);
        settings.setValue("dataFileType", IFS5200_CLICKED);
        QModelIndex fIndex = ui->treeView->currentIndex();
        QString fPath = fModel->fileInfo(fIndex).filePath();
        if (fModel->isDir(fIndex))
            return;
        QFile inFile(fPath);
        inFile.open(QIODevice::ReadOnly);
        ui->label->setText(fPath);

        const IFS_FILE_BLOCK *blockFileHeader;
        if (!readIfsFileHeader(&inFile, &fileHeader))
            qDebug("Error Reading File");
        blockFileHeader = reinterpret_cast<const IFS_FILE_BLOCK *>(fileHeader.constData());

        QString magicStr(fileHeader.left(4));
        QString locationStr(fileHeader.mid(12,8));       //need to change magic numbers
        QString nameStr(fileHeader.mid(36,24));       //need to change magic numbers

        const IFS_BLOCK *block;
        inFile.seek(96);            //set begining at start of block header

        for( size_t j=0; j<2; j++ )
        {
             ifs5200_data[j].clear( );
        }

         int loop = 0;
        while ( (inFile.atEnd() != true) )
        {
             ui->progressBar_input->setValue(1+100*inFile.pos()/inFile.size());
             loop++;

             if (!readNextIfsHeader((&inFile), &header))
                qDebug("Error Reading File");

             block = reinterpret_cast<const IFS_BLOCK *>(header.constData());

             qint64 firstBlockTimestamp = block->utm;

             double timestampMSecs = (double)firstBlockTimestamp * double(1000);
             QDateTime mSecsEpoch;
             mSecsEpoch.setMSecsSinceEpoch(timestampMSecs);

             ui->fileExtension->setText(magicStr);
             ui->location->setText(locationStr);
             ui->sensorName->setText(nameStr);
             ui->numberOfChannels->setText("2");
             ui->sampleFrequency->setText(QString::number(block->mainNumSamples,'g',6));

             if (!readNextData(&inFile, &data, (8*(block->mainNumSamples))))
                break;

             sample = reinterpret_cast<const qint32 *>(data.constData());



             for( size_t j=0; j<2; j++ )
             {
                raw.clear();

                for (size_t i=0; i<(block->mainNumSamples); i++)
                {
                   double y = (double)*sample++;

                   if (y > 8388607)
                   {
                           y -= 16777216;
                   }//end else


                   double value = y;
                   value *= SCALE;

                   raw.push_back( value );

                   ifs5200_data[j].append( value );

                   if(j == 0)
                   {
                       double MsecSinceBlockStart = i * (1000 / double(block->mainNumSamples));
                       QDateTime currentTime = mSecsEpoch.addMSecs(MsecSinceBlockStart);
                       x.append(currentTime.toMSecsSinceEpoch());
                   }
                }
             }

           count ++;
           ui->fileLength->setText(QString::number(count));
           }
        ui->fileLength->setText(QString::number(count));

        for (size_t i=0; i<((block->mainNumSamples)*count); i++)
        {
              double *press1=  ifs5200_data[0].data();
              double *press2=  ifs5200_data[1].data();

              double pressAdd = (( press1[i] / (doublePressCal1/1000 )) +  (press2[i] / (doublePressCal1/1000 ))) / 2;
              double accel = press1[i] - press2[i];

              if(i < 3)
              {
                  qDebug() << pressAdd << endl;
              }

              ifs5200_pressure[0].append(pressAdd);
              ifs5200_pressure[1].append(accel);
              ifs5200_accel[0].append(accel);

         }

        inFile.close();
    }


    if (SensorSelected == "DIG-8207")
    {
        x.clear();
        QDirModel *fModel = new QDirModel(this);
        settings.setValue("dataFileType", DIG8107_CLICKED);
        QModelIndex fIndex = ui->treeView->currentIndex();
        QString fPath = fModel->fileInfo(fIndex).filePath();
        if (fModel->isDir(fIndex))
            return;
        QFile inFile(fPath);
        inFile.open(QIODevice::ReadOnly);
        ui->label->setText(fPath);

        ui->WriteData->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);

        double freq = 0;

        const DIG8207_FILE_BLOCK *blockFileHeader;
        if (!readFileDIG8207Header(&inFile, &fileHeader))
            qDebug("Error Reading File");
        blockFileHeader = reinterpret_cast<const DIG8207_FILE_BLOCK *>(fileHeader.constData());

        QString magicStr(fileHeader.left(4));
        QString locationStr(fileHeader.mid(12,8));       //need to change magic numbers
        QString nameStr(fileHeader.mid(36,24));       //need to change magic numbers

        // QString magicStr(header.left(4));
        const DIG8207_BLOCK *block;
        inFile.seek(96);            //set begining at start of block header
         int loop = 0;

         for( size_t j=0; j<8; j++ )
         {
              dig8207_data[j].clear( );
         }
        //for( size_t j=0; j<1; j++ )

        while ( (inFile.atEnd() != true) )
        {
             ui->progressBar_input->setValue(1+100*inFile.pos()/inFile.size());
             loop++;

             if (!readNextDIG8207Header((&inFile), &header))
                qDebug("Error Reading File");

             block = reinterpret_cast<const DIG8207_BLOCK *>(header.constData());

             qint64 firstBlockTimestamp = block->utm;
             double timestampMSecs = (double)firstBlockTimestamp * double(1000);
             QDateTime mSecsEpoch;
             mSecsEpoch.setMSecsSinceEpoch(timestampMSecs);

             ui->fileExtension->setText(magicStr);
             ui->location->setText(locationStr);
             ui->sensorName->setText(nameStr);
             ui->numberOfChannels->setText(QString::number(block->numChannels,'g',6));
             freq = (block->mainNumSamples)/(block->numChannels);
             ui->sampleFrequency->setText(QString::number(freq));

             if (!readNextData(&inFile, &data, (4*(block->mainNumSamples))))
             //if (!readNextData(&inFile, &data, (32000)))
             break;

             sample = reinterpret_cast<const qint32 *>(data.constData());

             for( size_t j=0; j<8; j++ )
             {
                raw.clear();

                for (size_t i=0; i<(freq); i++)
                {
                   double y = (double)*sample++;

                   if (y > 8388607)
                   {
                           y -= 16777216;
                   }//end else

                   double value = y;
                   value *= SCALE;

                   raw.push_back( value );

                   dig8207_data[j].append( value );

                   if(j == 0)
                   {
                      // double MsecSinceBlockStart = i * (1000 / double(block->mainNumSamples));
                       double MsecSinceBlockStart = i * (1000 / freq);
                       QDateTime currentTime = mSecsEpoch.addMSecs(MsecSinceBlockStart);
                       x.append(currentTime.toMSecsSinceEpoch());
                   }
                }
             }

           count ++;
         //  ui->fileLength->setText(QString::number(count));
           }
        ui->fileLength->setText(QString::number(count));
        ui->progressBar_input->setValue(1+100*(inFile.pos()/inFile.size()));
        inFile.close();
    }

    if (SensorSelected == "DIG-8107")
    {
         x.clear();
        int count = 0;
        double msecSinceBlockStart;
        QDateTime sampleTime;
        QDirModel *fModel = new QDirModel(this);
        settings.setValue("dataFileType", DIG8207_CLICKED);
        QModelIndex fIndex = ui->treeView->currentIndex();
        QString fPath = fModel->fileInfo(fIndex).filePath();
        if (fModel->isDir(fIndex))
            return;
        QFile inFile(fPath);
        inFile.open(QIODevice::ReadOnly);
        ui->label->setText(fPath);

        ui->WriteData->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);

        int channels;
        const DIG8107_BLOCK *block;
        const DIG8107_BLOCK_FOOTER *blockFooter;
        if (!readNextDIG8107Header(&inFile, &header))
            qDebug("Error Reading File");

        block = reinterpret_cast<const DIG8107_BLOCK *>(header.constData());

        inFile.seek(0);
        x.clear();
        for (int i=0; i<8; i++)
            dig8107_data[i].clear();

        QString nameStr(header.mid(8,40));       //need to change magic numbers
        ui->sensorName->setText(nameStr);

        qint64 decimationNanoSecPerSampleTest = block->nanoSecondsPerSample * block->acousticDecimationLevel;
        qint64 firstBlockTimestampTest = block->lastTimestamp - (decimationNanoSecPerSampleTest * block->numSamplesPerChannel);
        double timestampMSecsTest = ((double)firstBlockTimestampTest - (double)block->correlationTimestamp)/(double)1000000.0;

        QDateTime epochTest;
        epochTest.setMSecsSinceEpoch((block->correlationSecs * (qint64)1000) + (block->correlationUSecs/(qint64)1000));
        QDateTime blockTimeTest = epochTest.addMSecs(timestampMSecsTest);
        double sampleTimeTest = blockTimeTest.toMSecsSinceEpoch();

        // for (int i=0; i<3;i++)

        for( size_t j=0; j<8; j++ )
        {
             dig8107_data[j].clear( );
        }

        while ( (inFile.atEnd() != true)  )
        {

            if (!readNextDIG8107Header(&inFile, &header))
                break;
            //   ui->dataType->setText(QString::number(block->dataTypeOld));
            //   ui->nanoSecondsPerSample->setText(QString::number(block->nanoSecondsPerSa

            //                           if((block->nanoSecondsPerSample)!=66672)
            //                   {
            //                       qDebug("Error numSamplesPerChannel");

            //                   }mpleOld));
            //   ui->dataSize->setText(QString::number(block->dataSizeOld));
            channels = block->numChannels;
            ui->numberOfChannels->setText(QString::number(block->numChannels));
            count ++;

            ui->sampleFrequency->setText(QString::number((1000000000.0/block->nanoSecondsPerSample),'f', 4));

            block = reinterpret_cast<const DIG8107_BLOCK *>(header.constData());         //push pointer up to data

            if (!readNextData(&inFile, &data, block->dataSize))                          //read data
                break;

            qint64 decimationNanoSecPerSample = block->nanoSecondsPerSample * block->acousticDecimationLevel;
            qint64 firstBlockTimestamp = block->lastTimestamp - (decimationNanoSecPerSample * block->numSamplesPerChannel);
            double timestampMSecs = ((double)firstBlockTimestamp - (double)block->correlationTimestamp)/(double)1000000.0;

           // qDebug(" timestampMSecs ");
           // qDebug() << timestampMSecs << endl;
            //  QDateTime mSecsEpoch;
            //   mSecsEpoch.setMSecsSinceEpoch(timestampMSecs);

            QDateTime epoch;
            epoch.setMSecsSinceEpoch((block->correlationSecs * (qint64)1000) + (block->correlationUSecs/(qint64)1000));
            QDateTime blockTime = epoch.addMSecs(timestampMSecs);


           // qDebug() << blockTime << endl;

            sample = reinterpret_cast<const qint32 *>(data.constData());

            for( size_t j=0; j<block->numChannels; j++ )
            {
                raw.clear();

                for (size_t i=0; i<block->numSamplesPerChannel; i++)
                {
                    double value = (double)*sample++ * SCALE;

                    raw.push_back( value );
                    dig8107_data[j].append( value );

                    if(j == 0)
                    {
                        //need to populate x axis
                        //This uses nanoSec/Sample to figure out how to increment over each chunk of data
                        //These chunks can be of different size
                        //This increments are added to the timestamp of the first chunk of the file

                        msecSinceBlockStart = ((double)i * (double)decimationNanoSecPerSample)/ (double)1000000.0;  //this can be different for different size chunks
                      //  qDebug(" msecSinceBlockStart ");
                     //   qDebug() << msecSinceBlockStart << endl;
                        x.append(sampleTimeTest + msecSinceBlockStart);

                    }
                }

            }

            //We have to keep up with where we are at in time for the next chunk of data
            //so we push the begining of chunk timestamp to the end of the previous chunk
            //have to add in one sample's worth of time because the above loop in indexed with a 0
            sampleTimeTest = sampleTimeTest + msecSinceBlockStart + (((double)decimationNanoSecPerSample)/ (double)1000000.0);

            blockFooter = reinterpret_cast<const DIG8107_BLOCK_FOOTER *>(footer.constData());

            if (!readNextDigFooter(&inFile, &footer))
                qDebug("Error Reading FilePlotDatae");
            ui->progressBar_input->setValue(1+100*inFile.pos()/inFile.size());
        }

        inFile.close();
    }

}

void MainWindow::on_pushButton_clicked()
{
    QString SensorSelected = ui->SensorComboBox->currentText();

    dX.clear();

    for (int i=0; i<x.size(); i++)
    {
        dX.append((double)x.at(i)/1000.0);
    }

    // need to create own class and remove if
    if (SensorSelected == "IFS-5200")
    {

        PlotData plotdata;

        QDirModel *fModel = new QDirModel(this);
        QModelIndex fIndex = ui->treeView->currentIndex();
        QString fPath = fModel->fileInfo(fIndex).filePath();
        fPath = (fPath.left(fPath.length()-4));

        plotdata.plot(fPath, dX, ifs5200_data, SensorSelected);                 //set up if statement to grab different data
        plotdata.setModal(true);
        plotdata.exec();
    }
    if (SensorSelected == "DIG-8207")
    {

        PlotDigData plotdigdata;
        QDirModel *fModel = new QDirModel(this);
        QModelIndex fIndex = ui->treeView->currentIndex();
        QString fPath = fModel->fileInfo(fIndex).filePath();
        fPath = (fPath.left(fPath.length()-4));

        plotdigdata.plot(fPath, dX, dig8207_data, SensorSelected);                 //set up if statement to grab different data
        plotdigdata.setModal(true);
        plotdigdata.exec();

    }

    if (SensorSelected == "DIG-8107")
    {

        PlotDigData plotdigdata;
        QDirModel *fModel = new QDirModel(this);
        QModelIndex fIndex = ui->treeView->currentIndex();
        QString fPath = fModel->fileInfo(fIndex).filePath();
        fPath = (fPath.left(fPath.length()-4));

        plotdigdata.plot(fPath, dX, dig8107_data, SensorSelected);                 //set up if statement to grab different data
        plotdigdata.setModal(true);
        plotdigdata.exec();

    }

}

bool MainWindow::readIfsFileHeader(QFile *file, QByteArray *header)
{
    *header = file->read(sizeof(IFS_FILE_BLOCK));

    if (header->size() != sizeof(IFS_FILE_BLOCK))
        return false;

    return true;
}


bool MainWindow::readNextIfsHeader(QFile *file, QByteArray *header)
{
    *header = file->read(sizeof(IFS_BLOCK));

    if (header->size() != sizeof(IFS_BLOCK))
        return false;

    return true;
}

bool MainWindow::readFileDIG8207Header(QFile *file, QByteArray *header)
{
    *header = file->read(sizeof(DIG8207_FILE_BLOCK));

    if (header->size() != sizeof(DIG8207_FILE_BLOCK))
        return false;

    return true;
}


bool MainWindow::readNextDIG8207Header(QFile *file, QByteArray *header)
{
    *header = file->read(sizeof(DIG8207_BLOCK));

    if (header->size() != sizeof(DIG8207_BLOCK))
        return false;

    return true;
}

bool MainWindow::readNextDIG8107Header(QFile *file, QByteArray *header)
{
    *header = file->read(sizeof(DIG8107_BLOCK));

    if (header->size() != sizeof(DIG8107_BLOCK))
        return false;

    return true;
}

bool MainWindow::readNextDigFooter(QFile *file, QByteArray *footer)
{
    *footer = file->read(sizeof(DIG8107_BLOCK_FOOTER));

    if (footer->size() != sizeof(DIG8107_BLOCK_FOOTER))
        return false;

    return true;
}

bool MainWindow::readNextData(QFile *file, QByteArray *data, qint64 length)
{
    *data = file->read(length);
    if (data->size() != length)
        return false;

    return true;
}


#define NANOSECONDS_PER_SEC 1000000000
void MainWindow::timestampToSecUsec(quint64 timestamp, quint32 *secs, quint32 *usecs)
{
   quint64 temp = timestamp / NANOSECONDS_PER_SEC;
   *secs = temp;
   *usecs = timestamp - (temp * NANOSECONDS_PER_SEC);
   *usecs /= 1000;
}


void MainWindow::on_WriteData_clicked()
{
    char *outBuf = new char[256];
    QDirModel *fModel = new QDirModel(this);
    QModelIndex fIndex = ui->treeView->currentIndex();
    QString fPath = fModel->fileInfo(fIndex).filePath();
    fPath = (fPath.left(fPath.length()-3).append("out"));
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               fPath);
    QString SensorSelected = ui->SensorComboBox->currentText();
    if (SensorSelected == "IFS-5200")
    {

        if (fileName != NULL)
        {
            QFile outFile(fileName);
            outFile.open(QIODevice::WriteOnly);

            for (int i=0; i<x.size(); i++)
            {
                char *tempX;
                QByteArray tempX2;
                QDateTime timeOut;
                timeOut = QDateTime::fromMSecsSinceEpoch(x.at(i));
                tempX2.append(timeOut.toString("yyyyMMMdd hh:mm:ss.zzz"));
                tempX = tempX2.data();    ui->SensorComboBox->addItem("DIG-8207");

                sprintf(outBuf, "%s %016.13f %016.13f\n",
                        tempX, ifs5200_data[0].at(i), ifs5200_data[1].at(i));
                outFile.write(outBuf, strlen(outBuf));
                ui->progressBar->setValue(100*i/x.size());
            }
            outFile.close();
        }

    }

    if (SensorSelected == "DIG-8107")
    {

        if (fileName != NULL)
        {
            QFile outFile(fileName);
            outFile.open(QIODevice::WriteOnly);

            for (int i=0; i<x.size(); i++)
            {
                char *tempX;
                QByteArray tempX2;
                QString delim = ".";
                QDateTime timeOut;
              //  qDebug(" x.at(i) ");
              //  qDebug()  << qSetRealNumberPrecision( 15 ) << x.at(i) << endl;

                QString valueAsString = QString("%1").arg(x.at(i),0,'f',2);
               //  qDebug()  << valueAsString << endl;
                int pos = valueAsString.indexOf(delim);
                QString nano = valueAsString.right(2);
               // qDebug()  << nano << endl;
                timeOut = QDateTime::fromMSecsSinceEpoch(x.at(i));

                tempX2.append(timeOut.toString("yyyyMMMdd hh:mm:ss.zzz"));

                tempX2.append(nano);

               // qDebug() << tempX2 << endl;
                tempX = tempX2.data();    ui->SensorComboBox->addItem("DIG-8207");


                sprintf(outBuf, "%s %016.13f %016.13f %016.13f %016.13f %016.13f %016.13f %016.13f %016.13f\n",
                        tempX, dig8107_data[0].at(i), dig8107_data[1].at(i),dig8107_data[2].at(i),dig8107_data[3].at(i),dig8107_data[4].at(i),dig8107_data[5].at(i),dig8107_data[6].at(i),dig8107_data[7].at(i));
                outFile.write(outBuf, strlen(outBuf));
                ui->progressBar->setValue(100*i/x.size());
            }
            outFile.close();
        }
    }


}



void MainWindow::on_setDefaultPath_clicked()
{
    QDirModel *fModel = new QDirModel(this);
    QModelIndex fIndex = ui->treeView->currentIndex();
    QString newIndex = fModel->fileInfo(fIndex).filePath();
    ui->defaultFilePath->setText(newIndex);
    settings.setValue("defaultFilePath", newIndex);
}

void MainWindow::refreshDir()
{
    QModelIndex index = ui->treeView->currentIndex();
    dirModel->refresh(index);
}

void MainWindow::on_pushButton_2_clicked()
{
     saveSettings();
}

void MainWindow::loadSettings()
{
    int test = 1;
    qDebug() << test << endl;

    QSettings settings("parsePlotSettings.ini", QSettings::IniFormat);

    //Load up default Calibration levels
    QString sTextPressCal1 = settings.value("PressCal1").toString();
    QString sTextPressCal2 = settings.value("PressCal2").toString();
    QString sTextAccelCal1 = settings.value("AccelCal1").toString();
    QString sTextAccelCal2 = settings.value("AccelCal2").toString();

    doublePressCal1 = settings.value("PressCal1").toDouble();
    doublePressCal2 = settings.value("PressCal1").toDouble();
    doubleAccelCal1 = settings.value("PressCal1").toDouble();
    doubleAccelCal2 = settings.value("PressCal1").toDouble();

    ui->WriteData->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);


    if (ui->m_pLabelPressCal1)
    {
         ui->m_pLabelPressCal1->setText(sTextPressCal1);
    }

    if (ui->m_pLabelPressCal2)
    {
         ui->m_pLabelPressCal2->setText(sTextPressCal2);
    }

    if (ui->m_pLabelAccelCal1)
    {
         ui->m_pLabelAccelCal1->setText(sTextAccelCal1);
    }

    if (ui->m_pLabelAccelCal2)
    {
         ui->m_pLabelAccelCal2->setText(sTextAccelCal2);
    }

     //Load up default Sensor type
    QString sTextSensorType = settings.value("SensorType").toString();

    ui->SensorComboBox->addItem("IFS-5200");
    ui->SensorComboBox->addItem("DIG-1107");
    ui->SensorComboBox->addItem("DIG-8107");
    ui->SensorComboBox->addItem("DIG-8207");

    int index = ui->SensorComboBox->findText(sTextSensorType);

    if(index >= 0)
    {
         ui->SensorComboBox->setCurrentIndex(index);
    }

}

void MainWindow::saveSettings()
{
    QSettings settings("parsePlotSettings.ini", QSettings::IniFormat);
    QString sTextPressCal1 = (ui->m_pLabelPressCal1) ? ui->m_pLabelPressCal1->text() : "";
    QString sTextPressCal2 = (ui->m_pLabelPressCal2) ? ui->m_pLabelPressCal2->text() : "";
     QString sTextAccelCal1 = (ui->m_pLabelAccelCal1) ? ui->m_pLabelAccelCal1->text() : "";    QString sTextAccelCal2 = (ui->m_pLabelAccelCal2) ? ui->m_pLabelAccelCal2->text() : "";

    bool PressCal1ok = false;
    bool PressCal2ok = false;
    bool AccelCal1ok = false;
    bool AccelCal2ok = false;

    double PressCal1read = sTextPressCal1.toDouble(&PressCal1ok);
    double PressCal2read = sTextPressCal2.toDouble(&PressCal2ok);
    double AccelCal1read = sTextAccelCal1.toDouble(&AccelCal1ok);
    double AccelCal2read = sTextAccelCal2.toDouble(&AccelCal2ok);

    if (PressCal1ok && PressCal2ok && AccelCal1ok && AccelCal2ok) // a double       //check to see if entered Cal levels are numbers.
    {
        qDebug() << PressCal1read << endl;
        qDebug() << PressCal1ok << endl;

        settings.setValue("PressCal1", sTextPressCal1);
        settings.setValue("PressCal2", sTextPressCal2);
        settings.setValue("AccelCal1", sTextAccelCal1);
        settings.setValue("AccelCal2", sTextAccelCal2);

        if (ui->m_pLabelPressCal1)
        {
             ui->m_pLabelPressCal1->setText(sTextPressCal1);
        }
        if (ui->m_pLabelPressCal2)
        {
             ui->m_pLabelPressCal2->setText(sTextPressCal2);
        }
        if (ui->m_pLabelAccelCal1)
        {
             ui->m_pLabelAccelCal1->setText(sTextAccelCal1);
        }
        if (ui->m_pLabelAccelCal2)
        {
             ui->m_pLabelAccelCal2->setText(sTextAccelCal2);
        }
        //    PlotAccel plotaccel;
        //    QDirModel *fModel = new QDirModel(this);
        //    QModelIndex fIndex = ui->treeView->currentIndex();
        //    QString fPath = fModel->fileInfo(fIndex).filePath();
        //    QString SensorSelected = ui->SensorComboBox->currentText();

        //    fPath = (fPath.left(fPath.length()-4));
        //    plotaccel.plot(fPath, dX, ifs5200_accel, SensorSelected);                 //set up if statement to grab different data
        //    plotaccel.setModal(true);
        //    plotaccel.exec();
    }
    else if(PressCal1ok == false)
    {
          QMessageBox msgBox;
          msgBox.setText("Bad Press Calibration for Channel A");
          msgBox.exec();
    }
    else if(PressCal2ok == false)
    {
          QMessageBox msgBox;
          msgBox.setText("Bad Press Calibration for Channel B");
          msgBox.exec();
    }
    else if(AccelCal1ok == false)
    {
          QMessageBox msgBox;
          msgBox.setText("Bad Accel Calibration for Channel A");
          msgBox.exec();
    }
    else if(AccelCal2ok == false)
    {
          QMessageBox msgBox;
          msgBox.setText("Bad Accel Calibration for Channel B");
          msgBox.exec();
    }


      QString SensorSelected = ui->SensorComboBox->currentText();         //read in sensor Dropbox
      settings.setValue("SensorType", SensorSelected);
      //    PlotAccel plotaccel;
      //    QDirModel *fModel = new QDirModel(this);
      //    QModelIndex fIndex = ui->treeView->currentIndex();
      //    QString fPath = fModel->fileInfo(fIndex).filePath();
      //    QString SensorSelected = ui->SensorComboBox->currentText();

      //    fPath = (fPath.left(fPath.length()-4));
      //    plotaccel.plot(fPath, dX, ifs5200_accel, SensorSelected);                 //set up if statement to grab different data
      //    plotaccel.setModal(true);
      //    plotaccel.exec();
}

void MainWindow::closeEvent( QCloseEvent* ev )
{

    saveSettings();



} // end closeEvent  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MainWindow::on_pushButton_3_clicked()
{
    dX.clear();

    for (int i=0; i<x.size(); i++)
    {
        dX.append((double)x.at(i)/1000.0);
    }

    PlotPressure plotpressure;
    QDirModel *fModel = new QDirModel(this);
    QModelIndex fIndex = ui->treeView->currentIndex();
    QString fPath = fModel->fileInfo(fIndex).filePath();
    QString SensorSelected = ui->SensorComboBox->currentText();

    fPath = (fPath.left(fPath.length()-4));
    plotpressure.plot(fPath, dX, ifs5200_pressure,SensorSelected);                 //set up if statement to grab different data
    plotpressure.setModal(true);
    plotpressure.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    dX.clear();

    for (int i=0; i<x.size(); i++)
    {
        dX.append((double)x.at(i)/1000.0);
    }

    PlotAccel plotaccel;
    QDirModel *fModel = new QDirModel(this);
    QModelIndex fIndex = ui->treeView->currentIndex();
    QString fPath = fModel->fileInfo(fIndex).filePath();
    QString SensorSelected = ui->SensorComboBox->currentText();

    fPath = (fPath.left(fPath.length()-4));
    plotaccel.plot(fPath, dX, ifs5200_accel, SensorSelected);                 //set up if statement to grab different data
    plotaccel.setModal(true);
    plotaccel.exec();
}
