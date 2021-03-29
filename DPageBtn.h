#pragma once

#include <QObject>
#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QFontMetrics>
#include "Struct.h"
class DPageBtn : public QWidget
{
    Q_OBJECT
    
public:
    DPageBtn(QWidget* parent, QString strText = "", btntype type = BUTTON_NONE);
    void SetDown(bool flag = false);	                                     //设置是否按下
    bool GetDown();                                                               //获取是否按下
    void SetText(QString text);                                                //设置按钮文字
    void SetDownColor(QColor color);
    void SetHoverColor(QColor color);
    void SetId(int id);
    void SetEnable(bool flag);
    int  GetId();
    ~DPageBtn();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent*);

signals:
    void PageBtnClienk();

private:
    bool              m_isDown;
    bool              m_isEnter;
    bool              m_isPressed;
    bool              m_isEnable;
    QString         m_Text;
    QColor          m_DownColor;
    QColor          m_HoverColor;
    int                 m_ID;
    int                 m_textHeight;
    int                 m_textWidth;

};
