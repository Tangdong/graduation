#include "DDialog.h"

DDialog::DDialog(int frameDlgWidth /*= -1*/, int frameDlgHeight /*= -1*/, QWidget *parent /*= NULL*/, bool hasShadow /*= true*/)
    : QDialog(parent)
{
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    setFocusPolicy(Qt::NoFocus);
    setFixedSize(frameDlgWidth, frameDlgHeight);
    m_nTitleHeight = 28 ;

    m_Titlelb = new QLabel("test");
    m_closeBtn = new QPushButton();
    m_closeBtn->setCheckable(true);
    m_closeBtn->setFixedSize(28, 28);
    m_closeBtn->setStyleSheet("QPushButton{border: none;}:!hover{border-image: url(:/GraduationDesign/Resources/icon_out_window_hover.png)}\
                              :hover{border: none; border-image: url(:/GraduationDesign/Resources/icon_out_window_hover.png)}\
                              :pressed{border: none; border-image: url(:/GraduationDesign/Resources/icon_out_window_click.png)}"
                              "QPushButton:focus{ outline: none; }");
    m_closeBtn->setFocusPolicy(Qt::NoFocus); //不用焦点

    QHBoxLayout *titlehbox = new QHBoxLayout;
    titlehbox->addWidget(m_Titlelb);
    titlehbox->addStretch();
    titlehbox->addWidget(m_closeBtn);
    titlehbox->setContentsMargins(20, 0, 0, 0);

    m_centerwidget = new QWidget;
    m_centerwidget->setFixedSize(frameDlgWidth - 2, frameDlgHeight - m_nTitleHeight - 1); //-2，-1是因为要画边框
    QHBoxLayout * hContentLayout = new QHBoxLayout();
    hContentLayout->setContentsMargins(1, 0, 1, 1);//左右留一个像素画边框
    hContentLayout->addWidget(m_centerwidget);
    hContentLayout->setSpacing(0);
    
    QVBoxLayout *vboxlay = new QVBoxLayout;
    vboxlay->addLayout(titlehbox);
    vboxlay->addLayout(hContentLayout);
    vboxlay->setContentsMargins(0, 0, 0, 0);
    setLayout(vboxlay);

    connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(OnCloseClicked()));
}

DDialog::~DDialog()
{
}

bool DDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;
    if (msg->message == WM_NCHITTEST)
    {
        int xPos = (int)(short)LOWORD(msg->lParam) - this->frameGeometry().x();
        int yPos = (int)(short)HIWORD(msg->lParam) - this->frameGeometry().y();
        QPoint curPt(xPos, yPos);
        if (this->childAt(curPt)) //鼠标在子窗口上就算了
        {
            return false;
        }
        *result = HTCAPTION;
        return true;
    }

    //去除阴影带来的边框问题
    else if (msg->message == WM_NCCALCSIZE)
    {
        *result = 0;
        return true;
    }
    else if (msg->message == WM_NCLBUTTONDBLCLK)
    {
        showNormal();
        return true;
    }

    return false;
}
void DDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        return;
    }
}
void DDialog::OnCloseClicked()
{
    emit sigCloseDlg();
}

void DDialog::setTitleName(QString text)
{
    m_Titlelb->setText(text);
}
void DDialog::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    int nWidth = width();
    int nheight = height();
    painter.fillRect(0, 0, nWidth, m_nTitleHeight, QColor(51, 146, 255));
    painter.fillRect(0, m_nTitleHeight, nWidth, nheight - m_nTitleHeight, QColor(255, 255, 255));//235, 240, 245灰

    painter.setPen(QColor(155, 160, 167));
    painter.drawLine(0, m_nTitleHeight, 0, nheight);                    //左
    painter.drawLine(0, nheight - 1, nWidth, nheight - 1);              //下
    painter.drawLine(nWidth - 1, m_nTitleHeight, nWidth - 1, nheight);  //右
}

void DDialog::setContentWidget(QWidget* contentWdg)
{
    QVBoxLayout* vblContent = new QVBoxLayout;
    vblContent->setContentsMargins(0, 0, 0, 0);
    vblContent->setSpacing(0);
    vblContent->addWidget(contentWdg);
    m_centerwidget->setLayout(vblContent);
    // m_contentWidget->setStyleSheet("QWidget{background-color: red}");
}
