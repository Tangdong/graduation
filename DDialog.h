#pragma once

#include <QDialog>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QMouseEvent>
#include <windows.h>

class DDialog : public QDialog
{
    Q_OBJECT

public:
    DDialog(int frameDlgWidth = -1, int frameDlgHeight = -1, QWidget *parent = NULL, bool hasShadow = true);  //hasShadow�Ƿ���Ҫ�߿���Ӱ���в��ֵ������˱߿���Ӱ�������
    ~DDialog();
    void setContentWidget(QWidget* contentWdg);
    void setTitleName(QString text);
protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private slots:
    void  OnCloseClicked();
private:
    int m_nTitleHeight; //��������
    QLabel *m_Titlelb;
    QPushButton *m_closeBtn;
    QWidget *m_centerwidget;
signals:
    void sigCloseDlg();
};
