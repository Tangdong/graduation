#pragma once

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QTableWidget>
#include <QWidget>
#include <QtGui>
#include <QMouseEvent>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QScrollBar>


class DTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    DTableWidget(QWidget *parent = NULL);
    ~DTableWidget();
    void MySetItem( QStringList list);
    void DeletItem(int row);
    void ClearTable();
    QString GetIndexText(int row, int column);
private:
    void mouseDoubleClickEvent(QMouseEvent *event);
    QScrollBar *m_verticalBar;
private slots:
    void Ontest(int a);
signals:
    void sendDoubleClickItem(QTableWidgetItem *);
    void OnScrollBarArriveBottom();
};
