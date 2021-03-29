#include "DLFUNC.h"

QWidget* g_Graduation;
QTcpSocket* g_Socket;
struct Userinfo *g_userinfo;

int DLFUNC::GetTextWidth(QFont font, QString str)
{
    QFontMetrics metrics(font);
    return metrics.width(str);
}

QString DLFUNC::GetHintString(const QFont& font, QString& str, int width, Qt::TextElideMode mode)
{
    QFontMetrics metrics(font);
    return metrics.elidedText(str,mode,width);
}

QString DLFUNC::GetIndexText(unsigned long n)
{
    QString line;
    //获取程序当前运行目录
    QString fileName = QCoreApplication::applicationDirPath();
    QFile file(fileName + "./en.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);  //用文件构造流
        QString text = in.readLine();//读取一行放到字符串里
        while (!text.isEmpty())
        {
            QString textnum = text.mid(0, 5);
            if (textnum == QString("%1").arg(n))
            {
                line = text.mid(6);
                return line;
            }
            text = in.readLine();
        }

        qDebug() << line;

    }
    file.close();
    return "";
}

void DLFUNC::WriteLogText(QTextStream in,QString text)
{



}
double DLFUNC::GetDaysfrommesc(qint64 ms)
{
    double dayMecs = 1000 * 60 * 60 * 24; //一天有多少毫秒
    return (double)(ms / dayMecs);
}

double DLFUNC::GetHourfrommesc(qint64 ms)
{
    double hourMecs = 1000 * 60 * 60;
    return (double)(ms / hourMecs);
}

bool DLFUNC::SearchItem(Bookinfo &book,QString str, int statu)
{
    bool result = false;

    switch (statu)
    {
    case BOOKNUM:
        if (book.booknum.contains(str))
        {
            result = true;
        }
        break;
    case BOOKNAME:
        if (book.bookname.contains(str))
        {
            result = true;
        }
        break;
    case CATAGORY:
        if (book.catagory.contains(str))
        {
            result = true;
        }
        break;
    case AUTHOR:
        if (book.author.contains(str))
        {
            result = true;
        }
        break;
    default:
        break;
    }

    return result;
}
