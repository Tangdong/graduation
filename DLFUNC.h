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
    //�õ����ֵĳ��ȣ�XXXX -> ����Ϊ10
    int GetTextWidth(QFont font, QString str);
    //���ֹ����ı������ʽ��XXXXX ->XX....
    QString GetHintString(const QFont& font, QString& str, int width = 100, Qt::TextElideMode mode = Qt::ElideRight);
    //ͨ�������ҵ�����
    QString GetIndexText(unsigned long n);
    //д����־�鿴���͵���Ϣ
    void WriteLogText(QTextStream in,QString text);
    //���뻻�����
    double GetDaysfrommesc(qint64 ms);
    //���뻻��Сʱ
    double GetHourfrommesc(qint64 ms);
    //����ʱ�Ƿ����
    bool SearchItem(Bookinfo &book, QString str, int statu);
};

