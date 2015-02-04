#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "./Common/FireFlyDefs.h"
//#include "./Common/FireFlyDefsOld.h"
#include "./Common/IfsDefs.h"
#include "./Common/DigDefs.h"

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDirModel>
#include <QFileSystemModel>

#define RAW_CLICKED 0
#define SYNTRO_OLD_GPS_CLICKED 1
#define IFS5200_CLICKED 2
#define DIG8107_CLICKED 3
#define DIG8207_CLICKED 4

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString fPath;

protected:
   void closeEvent( QCloseEvent* ev );

private:
    Ui::MainWindow *ui;
    QDirModel           *dirModel;
    QFileSystemModel    *fileModel;
    bool readIfsFileHeader(QFile *file, QByteArray *header);
    bool readNextIfsHeader(QFile *file, QByteArray *header);

    bool readNextDIG8107Header(QFile *file, QByteArray *header);
    bool readNextDigFooter(QFile *file, QByteArray *header);


    bool readFileDIG8207Header(QFile *file, QByteArray *header);
    bool readNextDIG8207Header(QFile *file, QByteArray *header);




    void saveSettings();
    void loadSettings();


    bool readNextHeaderOld(QFile *file, QByteArray *header);


    bool readNextData(QFile *file, QByteArray *data, qint64 length);
    void timestampToSecUsec(quint64 timestamp, quint32 *secs, quint32 *usecs);
   // QVector <double> m_data[2], raw, x, dX;

    QVector <double> ifs5200_data[6], ifs5200_pressure[2], ifs5200_accel[1],raw, x, dX;
    QVector <double> dig8207_data[8];
    QVector <double> dig8107_data[8];
    QString newIndex;
    static int pdfCount;
    QString m_sSettingsFile;
  //  QLineEdit* m_pEdit;

private slots:
    void on_setDefaultPath_clicked();
    void on_treeView_doubleClicked(QModelIndex index);
    void on_WriteData_clicked();
    void on_pushButton_clicked();
    void refreshDir();
    void on_pushButton_2_clicked();
   // void on_lineEditCal1_returnPressed();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // MAINWINDOW_H
