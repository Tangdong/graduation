#include "DPageBtn.h"

DPageBtn::DPageBtn(QWidget* parent, QString strText /* = ""*/, btntype type /*= BUTTON_NONE*/)
    : QWidget(parent)
{
    m_isEnter  = false;
    m_isDown = false;
    m_isPressed = false;
    m_isEnable = false;
    m_ID = 0;
    m_textHeight = 0;
    m_textWidth  = 0;
    m_Text = strText;
    if (!strText.isEmpty())
    {
        SetText(strText);
    }

    switch (type)
    {
    case BUTTON_NONE:
        setFixedSize(30, 30);
        break;
    case BUTTON_TEXT:
        m_DownColor = QColor(224, 224, 224);
        m_HoverColor = QColor(100, 213, 35);
        setFixedSize(100, 40);
        break;
    case BUTTON_HOME:
        m_DownColor = QColor(224, 224, 224);
        m_HoverColor = QColor(100, 213, 35);
        setFixedSize(100,100);
        break;
    case BUTTON_ICON:
        break;
    default:
        break;
    }


}

void DPageBtn::SetEnable(bool flag)
{
    m_isEnable = flag;
}
void DPageBtn::SetDown(bool flag)
{
    m_isDown = flag;
    update();
}

bool DPageBtn::GetDown()
{
    return m_isDown;
}

void DPageBtn::SetText(QString text)
{
    m_Text = text;
    QFontMetrics metric(font());    //得到语言文字长度
    m_textHeight = metric.height();
    m_textWidth = metric.width(text);
    int w = m_textWidth + 30;
    if ( w < 80 )
    {
        w = 80;
    }
   // setFixedWidth(w);
    update();
}

void DPageBtn::SetDownColor(QColor color)
{
    m_DownColor = color;
}

void DPageBtn::SetHoverColor(QColor color)
{
    m_HoverColor = color;
}

void DPageBtn::SetId(int id)
{
    m_ID = id;
}

int DPageBtn::GetId()
{
    return m_ID;
}



DPageBtn::~DPageBtn()
{
}

void DPageBtn::paintEvent(QPaintEvent* event)
{

    
    int w = width();
    int h = height();
    QPainter painter(this);
    if (m_isEnable)
    {
        painter.fillRect(0, 0, w, h, QColor(111, 111, 111));
        goto NEXT;
    }
    if ( m_isDown )
    {
        if ( m_isEnter )
        {
            painter.fillRect(0, 0, w, h, m_HoverColor);
        }
        else
        {
            painter.fillRect(0, 0, w, h, m_DownColor);
        }
    }
    else
    {
        if (m_isEnter)
        {
            painter.fillRect(0, 0, w, h, m_HoverColor);
        }
        else
        {
            painter.fillRect(0, 0, w, h, QColor(111, 111, 111));
        }
    }
NEXT:
    painter.drawText(w/2 -  m_textWidth/2,h/2+m_textHeight/2,m_Text);
}

void DPageBtn::mousePressEvent(QMouseEvent* event)
{
    m_isPressed = true;
}

void DPageBtn::mouseReleaseEvent(QMouseEvent* event)
{
    if ( m_isPressed && !m_isEnable)
    {
        emit PageBtnClienk();
        m_isPressed = false;
    }
}

void DPageBtn::enterEvent(QEvent*)
{
    m_isEnter = true;
    update();
}

void DPageBtn::leaveEvent(QEvent*)
{
    m_isEnter = false;
    update();
}
