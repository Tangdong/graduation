#pragma once
#include <QWidget>
#include <QTcpSocket>
#include <QFile>
#include <QCoreApplication>
#include "DLFUNC.h"
#include "Struct.h"

extern QWidget* g_Graduation;
extern QTcpSocket* g_Socket;
extern struct Userinfo *g_userinfo;

namespace DLFUNC
{
    //得到文字的长度，XXXX -> 长度为10
    int GetTextWidth(QFont font, QString str);
    //文字过长改变表现形式，XXXXX ->XX....
    QString GetHintString(const QFont& font, QString& str, int width = 100, Qt::TextElideMode mode = Qt::ElideRight);
    //通过索引找到文字
    QString GetIndexText(unsigned long n);
    //写入日志查看发送的消息
    void WriteLogText(QTextStream in,QString text);
    //毫秒换算成天
    double GetDaysfrommesc(qint64 ms);
    //毫秒换成小时
    double GetHourfrommesc(qint64 ms);
    //搜索时是否存在
    bool SearchItem(Bookinfo &book, QString str, int statu);
};

