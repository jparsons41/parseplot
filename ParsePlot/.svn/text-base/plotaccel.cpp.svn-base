#include "plotaccel.h"
#include "ui_plotaccel.h"
#include "mainwindow.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPointF>
#include <QMenu>
#include <QFileDialog>
#include <QPrintDialog>
#include <limits>

int xPosAccel;

PlotAccel::PlotAccel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotAccel)
{
    ui->setupUi(this);

   // MainWindow newMain;
    letxScale = 1;
    letyScale = 1;
    //newMain.showMaximized();
}

PlotAccel::~PlotAccel()
{
    for (int i=0; i<1; i++)
        ui->plot->graph(i)->clearData();

    ui->plot->clearGraphs();
    ui->plot->clearItems();
    ui->plot->clearPlottables();
    ui->plot->removeGraph(0);
    qDebug("~PlotAccel");
    delete ui;
}

void PlotAccel::plot(QString fpath, QVector<double> dX, QVector <double> dData[],QString SensorSelected)
{
    QString temp;
    QString line;

//   double yMax = std::numeric_limits<double>::max();

//   foreach(double p, dData[0])
//   {
//     yMax = qMax(yMax, p.x());
//   }

    fPath = fpath;
    ui->plot->yAxis->setLabel("Volts");
    ui->plot->xAxis->setLabel("Time");
    ui->plot->plotLayout()->insertRow(0);
    ui->plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->plot, fpath));
    ui->plot->clearGraphs();
    ui->plot->clearItems();
    ui->plot->clearPlottables();
    ui->plot->removeGraph(0);
    ui->plot->legend->setVisible(true);

    ui->plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->plot->xAxis->setDateTimeFormat("dd MMM, yyyy\nhh:mm:ss.zzz");
    ui->plot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));

    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  //  ui->plot->addGraph();
  //  ui->plot->graph(1)->setPen(QPen(Qt::red));

  //  ui->plot->addGraph();
  //  ui->plot->graph(2)->setPen(QPen(Qt::black));

  //  ui->plot->addGraph();
   // ui->plot->graph(3)->setPen(QPen(Qt::cyan));

  //  ui->plot->addGraph();
 //   ui->plot->graph(4)->setPen(QPen(Qt::darkGreen));

  //  ui->plot->addGraph();
 //   ui->plot->graph(5)->setPen(QPen(Qt::magenta));

    ui->plot->graph(0)->setName("Channel A");
 //   ui->plot->graph(1)->setName("Channel B");
 //   ui->plot->graph(2)->setName("Channel 3");
  //  ui->plot->graph(3)->setName("Channel 4");
  //  ui->plot->graph(4)->setName("Channel 5");
  //  ui->plot->graph(5)->setName("Channel 6");

    ui->plot->xAxis2->setVisible(true);
    ui->plot->xAxis2->setTickLabels(false);
    ui->plot->yAxis2->setVisible(true);
    ui->plot->yAxis2->setTickLabels(false);
    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));

    ui->plot->graph(0)->setData(dX, dData[0]);
  //  ui->plot->graph(1)->setData(dX, dData[1]);
   // ui->plot->graph(2)->setData(dX, dData[2]);
   // ui->plot->graph(3)->setData(dX, dData[3]);
   // ui->plot->graph(4)->setData(dX, dData[4]);
   // ui->plot->graph(5)->setData(dX, dData[5]);

    ui->plot->graph(0)->rescaleAxes();
  //  ui->plot->graph(1)->rescaleAxes(true);
   // ui->plot->graph(2)->rescaleAxes(true);
  //  ui->plot->graph(3)->rescaleAxes(true);
  //  ui->plot->graph(4)->rescaleAxes(true);
  //  ui->plot->graph(5)->rescaleAxes(true);

    ui->plot->yAxis->setRangeLower(-50);
    ui->plot->yAxis->setRangeUpper(50);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->plot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->plot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}

void PlotAccel::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);
  xPosAccel = pos.x();

  if (ui->plot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
      if(ui->plot->graph(0)->visible())
          menu->addAction("Remove Channel 1", this, SLOT(removeChannel1()));
      else
          menu->addAction("Add Channel 1", this, SLOT(addChannel1()));

//      if(ui->plot->graph(1)->visible())
//          menu->addAction("Remove Channel 2", this, SLOT(removeChannel2()));
//      else
//          menu->addAction("Add Channel 2", this, SLOT(addChannel2()));

//      if(ui->plot->graph(2)->visible())
//          menu->addAction("Remove Channel 3", this, SLOT(removeChannel3()));
//      else
//          menu->addAction("Add Channel 3", this, SLOT(addChannel3()));

//      if(ui->plot->graph(3)->visible())
//          menu->addAction("Remove Channel 4", this, SLOT(removeChannel4()));
//      else
//          menu->addAction("Add Channel 4", this, SLOT(addChannel4()));

//      if(ui->plot->graph(4)->visible())
//          menu->addAction("Remove Channel 5", this, SLOT(removeChannel5()));
//      else
//          menu->addAction("Add Channel 5", this, SLOT(addChannel5()));

//      if(ui->plot->graph(5)->visible())
//          menu->addAction("Remove Channel 6", this, SLOT(removeChannel6()));
//      else
//          menu->addAction("Add Channel 6", this, SLOT(addChannel6()));

      menu->addAction("Remove All Channels But 1", this, SLOT(removeAllBut1()));
      menu->addAction("Remove All Channels But 2", this, SLOT(removeAllBut2()));
     // menu->addAction("Remove All Channels But 3", this, SLOT(removeAllBut3()));
    //  menu->addAction("Remove All Channels But 4", this, SLOT(removeAllBut4()));
    //  menu->addAction("Remove All Channels But 5", this, SLOT(removeAllBut5()));
    //  menu->addAction("Remove All Channels But 6", this, SLOT(removeAllBut6()));
    //  menu->addAction("Add All Channels", this, SLOT(addAll()));
      menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  }
  else
  {
    menu->addAction("Zoom X&Y Full", this, SLOT(xFullZoom()));
        if (ui->plot->selectedGraphs().size() > 0)
    menu->addAction("Zoom Full X and Y", this, SLOT(xyFullZoom()));
      if (ui->plot->graphCount() > 0)
      menu->addAction("Zoom X 60 Seconds", this, SLOT(x60SecondZoom()));
    if (ui->plot->graphCount() > 0)
      menu->addAction("Zoom x 30 Seconds", this, SLOT(x30SecondZoom()));
    if (ui->plot->graphCount() > 0)
      menu->addAction("Zoom x 10 Seconds", this, SLOT(x10SecondZoom()));
    if (ui->plot->graphCount() > 0)
      menu->addAction("Zoom x 5 Seconds", this, SLOT(x5SecondZoom()));
    if (ui->plot->graphCount() > 0)
      menu->addAction("Zoom x 1 Second", this, SLOT(x1SecondZoom()));
    if (ui->plot->graphCount() > 0)
      menu->addAction("Zoom x 0.1 Second", this, SLOT(x1mSecondZoom()));
  }

  menu->popup(ui->plot->mapToGlobal(pos));
}

void PlotAccel::xFullZoom()
{
    ui->plot->graph(0)->rescaleAxes();
    ui->plot->yAxis->setRangeLower(-50);
    ui->plot->yAxis->setRangeUpper(50);
    ui->plot->replot();
    ui->scaleBoth->setChecked(true);
}

void PlotAccel::xyFullZoom()
{
    ui->plot->graph(0)->rescaleAxes();
    ui->plot->yAxis->setRangeLower(-50);
    ui->plot->yAxis->setRangeUpper(50);
    ui->plot->replot();
}

void PlotAccel::x60SecondZoom()
{
    ui->plot->xAxis->setRange(ui->plot->xAxis->pixelToCoord(xPosAccel),60,Qt::AlignCenter);
    ui->plot->replot();
}

void PlotAccel::x30SecondZoom()
{
    ui->plot->xAxis->setRange(ui->plot->xAxis->pixelToCoord(xPosAccel),30,Qt::AlignCenter);
    ui->plot->replot();
}

void PlotAccel::x10SecondZoom()
{
    ui->plot->xAxis->setRange(ui->plot->xAxis->pixelToCoord(xPosAccel),10,Qt::AlignCenter);
    ui->plot->replot();
}

void PlotAccel::x5SecondZoom()
{
    ui->plot->xAxis->setRange(ui->plot->xAxis->pixelToCoord(xPosAccel),5,Qt::AlignCenter);
    ui->plot->replot();
}

void PlotAccel::x1SecondZoom()
{
    ui->plot->xAxis->setRange(ui->plot->xAxis->pixelToCoord(xPosAccel),1,Qt::AlignCenter);
    ui->plot->replot();


}

void PlotAccel::x1mSecondZoom()
{
    ui->plot->xAxis->setRange(ui->plot->xAxis->pixelToCoord(xPosAccel),0.1,Qt::AlignCenter);
    ui->plot->replot();
}

void PlotAccel::addChannel1()
{
    ui->plot->graph(0)->setVisible(true);
    ui->plot->legend->item(0)->setTextColor(Qt::black);
    ui->plot->replot();
}

void PlotAccel::addChannel2()
{
    ui->plot->graph(1)->setVisible(true);
    ui->plot->legend->item(1)->setTextColor(Qt::black);
    ui->plot->replot();
}

//void PlotAccel::addChannel3()
//{
//  //  ui->plot->graph(2)->setVisible(true);
//   // ui->plot->legend->item(2)->setTextColor(Qt::black);
//  //  ui->plot->replot();
//}

//void PlotAccel::addChannel4()
//{
// //   ui->plot->graph(3)->setVisible(true);
//  //  ui->plot->legend->item(3)->setTextColor(Qt::black);
//  //  ui->plot->replot();
//}

//void PlotAccel::addChannel5()
//{
//  //  ui->plot->graph(4)->setVisible(true);
//  //  ui->plot->legend->item(4)->setTextColor(Qt::black);
//  //  ui->plot->replot();
//}

//void PlotAccel::addChannel6()
//{
//  //  ui->plot->graph(5)->setVisible(true);
//  //  ui->plot->legend->item(5)->setTextColor(Qt::black);
//   // ui->plot->replot();
//}

void PlotAccel::removeChannel1()
{
    ui->plot->graph(0)->setVisible(false);
    ui->plot->legend->item(0)->setTextColor(Qt::lightGray);
    ui->plot->replot();
}

void PlotAccel::removeChannel2()
{
    ui->plot->graph(1)->setVisible(false);
    ui->plot->legend->item(1)->setTextColor(Qt::lightGray);
    ui->plot->replot();
}

//void PlotAccel::removeChannel3()
//{
//  //  ui->plot->graph(2)->setVisible(false);
//  //  ui->plot->legend->item(2)->setTextColor(Qt::lightGray);
//  //  ui->plot->replot();
//}

//void PlotAccel::removeChannel4()
//{
//  //  ui->plot->graph(3)->setVisible(false);
//  //  ui->plot->legend->item(3)->setTextColor(Qt::lightGray);
//  //  ui->plot->replot();
//}

//void PlotAccel::removeChannel5()
//{
//  //  ui->plot->graph(4)->setVisible(false);
//  //  ui->plot->legend->item(4)->setTextColor(Qt::lightGray);
//  //  ui->plot->replot();
//}

//void PlotAccel::removeChannel6()
//{
//  //  ui->plot->graph(5)->setVisible(false);
//  //  ui->plot->legend->item(5)->setTextColor(Qt::lightGray);
//  //  ui->plot->replot();
//}

void PlotAccel::removeAllBut1()
{
    ui->plot->graph(1)->setVisible(false);
//    ui->plot->graph(2)->setVisible(false);
//    ui->plot->graph(3)->setVisible(false);
//    ui->plot->graph(4)->setVisible(false);
//    ui->plot->graph(5)->setVisible(false);
    ui->plot->legend->item(1)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(2)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(3)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(4)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(5)->setTextColor(Qt::lightGray);
    ui->plot->replot();
}

void PlotAccel::removeAllBut2()
{
    ui->plot->graph(0)->setVisible(false);
//    ui->plot->graph(2)->setVisible(false);
//    ui->plot->graph(3)->setVisible(false);
//    ui->plot->graph(4)->setVisible(false);
//    ui->plot->graph(5)->setVisible(false);
    ui->plot->legend->item(0)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(2)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(3)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(4)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(5)->setTextColor(Qt::lightGray);
    ui->plot->replot();
}

//void PlotAccel::removeAllBut3()
//{
//    ui->plot->graph(1)->setVisible(false);
//    ui->plot->graph(0)->setVisible(false);
//    ui->plot->graph(3)->setVisible(false);
//    ui->plot->graph(4)->setVisible(false);
//    ui->plot->graph(5)->setVisible(false);
//    ui->plot->legend->item(1)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(0)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(3)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(4)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(5)->setTextColor(Qt::lightGray);
//    ui->plot->replot();
//}

//void PlotAccel::removeAllBut4()
//{
//    ui->plot->graph(1)->setVisible(false);
//    ui->plot->graph(2)->setVisible(false);
//    ui->plot->graph(0)->setVisible(false);
//    ui->plot->graph(4)->setVisible(false);
//    ui->plot->graph(5)->setVisible(false);
//    ui->plot->legend->item(1)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(2)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(0)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(4)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(5)->setTextColor(Qt::lightGray);
//    ui->plot->replot();
//}

//void PlotAccel::removeAllBut5()
//{
//    ui->plot->graph(1)->setVisible(false);
//    ui->plot->graph(2)->setVisible(false);
//    ui->plot->graph(3)->setVisible(false);
//    ui->plot->graph(0)->setVisible(false);
//    ui->plot->graph(5)->setVisible(false);
//    ui->plot->legend->item(1)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(2)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(3)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(0)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(5)->setTextColor(Qt::lightGray);
//    ui->plot->replot();
//}

//void PlotAccel::removeAllBut6()
//{
//    ui->plot->graph(1)->setVisible(false);
//    ui->plot->graph(2)->setVisible(false);
//    ui->plot->graph(3)->setVisible(false);
//    ui->plot->graph(4)->setVisible(false);
//    ui->plot->graph(0)->setVisible(false);
//    ui->plot->legend->item(1)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(2)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(3)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(4)->setTextColor(Qt::lightGray);
//    ui->plot->legend->item(0)->setTextColor(Qt::lightGray);
//    ui->plot->replot();
//}

void PlotAccel::addAll()
{
    ui->plot->graph(0)->setVisible(true);
    ui->plot->graph(1)->setVisible(true);
//    ui->plot->graph(2)->setVisible(true);
//    ui->plot->graph(3)->setVisible(true);
//    ui->plot->graph(4)->setVisible(true);
//    ui->plot->graph(5)->setVisible(true);
    ui->plot->legend->item(0)->setTextColor(Qt::black);
    ui->plot->legend->item(1)->setTextColor(Qt::black);
//    ui->plot->legend->item(2)->setTextColor(Qt::black);
//    ui->plot->legend->item(3)->setTextColor(Qt::black);
//    ui->plot->legend->item(4)->setTextColor(Qt::black);
//    ui->plot->legend->item(5)->setTextColor(Qt::black);
    ui->plot->replot();
}


void PlotAccel::on_scaleOnlyY_pressed()
{
    ui->plot->axisRect()->setRangeZoom(Qt::Vertical);
}

void PlotAccel::on_scaleBoth_pressed()
{
    ui->plot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
}

void PlotAccel::on_scaleOnlyX_pressed()
{
    ui->plot->axisRect()->setRangeZoom(Qt::Horizontal);
}

void PlotAccel::on_savPDF_clicked()
{
    QFile pdfFile;
    QString pdfPath = fPath.append(".pdf");
    QString fn = QFileDialog::getSaveFileName(this, tr("Save PDF as..."),
                                             pdfPath, tr("PDF files (*.pdf);;All Files (*)"));
    if (fn.isEmpty())
        return;
    if (! (fn.endsWith(".pdf", Qt::CaseInsensitive)))
        fn += ".pdf"; // default

    ui->plot->savePdf(fn);
}

void PlotAccel::on_printButton_clicked()
{
    QPrinter p;

    QPrintDialog qp (&p, this);
    if (qp.exec() == QDialog::Accepted)
    {
        p.setOrientation(QPrinter::Landscape);
        QRect rect (0, 0, 288, 180);
        QPixmap qpm = ui->plot->toPixmap();

        QPainter painter;
        qpm.scaled(p.pageRect().width(), p.pageRect().height(), Qt::KeepAspectRatio);
        painter.begin (&p);
        painter.drawPixmap (0, 0, qpm);
        painter.end();
    }
}
