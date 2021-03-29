#include "DMessageBox.h"
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
DMessageBox::DMessageBox(int type)
{
    // 去掉问号，只保留关闭
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    m_btnShow = false;
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    //setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    m_strTitleName = tr("hello");
    m_strText = tr("到付件哦我的接口我的技术很快了了手动按计划欧东京佛我金佛ID奇偶龙佛唉  我记得释");
    setFixedSize(350, 200);
    m_Lable = new QLabel(m_strText);
    m_Lable->setAlignment(Qt::AlignCenter);     //居中显示
    m_Lable->setWordWrap(true);                     //自动换行
    if ( type == QMessageBox::Ok)
    {
        m_OkBtn = new DPageBtn(this, "确认", BUTTON_TEXT);
        m_OkBtn->setFixedSize(100, 40);
        QHBoxLayout* hbox = new QHBoxLayout;
        hbox->addWidget(m_OkBtn);
        QVBoxLayout* Vbox = new QVBoxLayout;
        Vbox->addWidget(m_Lable);
        Vbox->addLayout(hbox);
        setLayout(Vbox);
        connect(m_OkBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnOkBtnClienk()));

    }
    else if ( type == ( QMessageBox::Ok | QMessageBox::Cancel))
    {
        m_CloseBtn = new DPageBtn(this, "取消", BUTTON_TEXT);
        m_OkBtn = new DPageBtn(this, "确认", BUTTON_TEXT);
        QHBoxLayout* hbox = new QHBoxLayout;
        hbox->addWidget(m_OkBtn);
        hbox->addWidget(m_CloseBtn);
        QVBoxLayout* Vbox = new QVBoxLayout;
        Vbox->addWidget(m_Lable);
        Vbox->addLayout(hbox);
        setLayout(Vbox);
        connect(m_OkBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnOkBtnClienk()));
        connect(m_CloseBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnCloseBtnClienk()));
    }
}

DMessageBox::~DMessageBox()
{
}

void DMessageBox::paintEvent(QPaintEvent* event)
{
    //QPainter painter(this);
    //painter.fillRect(QRect(0, 43, width(), height()), QColor(255, 255, 255));
    //painter.setPen(QColor(255, 255, 255));
    //painter.drawText(15, 12, width() - 50, 50, Qt::AlignLeft, m_strTitleName);
    //painter.setPen(QColor(11, 43, 75));
    //painter.drawLine(0, 0, width(), 0);
    //painter.drawLine(0, 0, 0, height());
    //painter.drawLine(0, height() - 1, width(), height() - 1);
    //painter.drawLine(width() - 1, 0, width() - 1, height());
}

void DMessageBox::showEvent(QShowEvent* event)
{
}

void DMessageBox::OnOkBtnClienk()
{
    done(QMessageBox::Ok);
}

void DMessageBox::OnCloseBtnClienk()
{
    done(QMessageBox::Close);
}

