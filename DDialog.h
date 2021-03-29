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
    DDialog(int frameDlgWidth = -1, int frameDlgHeight = -1, QWidget *parent = NULL, bool hasShadow = true);  //hasShadow是否需要边框阴影，有部分弹窗用了边框阴影会出问题
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
    int m_nTitleHeight; //顶部长度
    QLabel *m_Titlelb;
    QPushButton *m_closeBtn;
    QWidget *m_centerwidget;
signals:
    void sigCloseDlg();
};
