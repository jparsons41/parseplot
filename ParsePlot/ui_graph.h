/********************************************************************************
** Form generated from reading UI file 'graph.ui'
**
** Created: Tue Feb 3 14:33:03 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPH_H
#define UI_GRAPH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Graph
{
public:
    QWidget *widget;

    void setupUi(QWidget *Graph)
    {
        if (Graph->objectName().isEmpty())
            Graph->setObjectName(QString::fromUtf8("Graph"));
        Graph->resize(928, 635);
        widget = new QWidget(Graph);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 9, 911, 621));

        retranslateUi(Graph);

        QMetaObject::connectSlotsByName(Graph);
    } // setupUi

    void retranslateUi(QWidget *Graph)
    {
        Graph->setWindowTitle(QApplication::translate("Graph", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Graph: public Ui_Graph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPH_H
