#include "DMessageBox.h"
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
DMessageBox::DMessageBox(int type)
{
    // ȥ���ʺţ�ֻ�����ر�
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    m_btnShow = false;
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    //setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    m_strTitleName = tr("hello");
    m_strText = tr("������Ŷ�ҵĽӿ��ҵļ����ܿ������ֶ����ƻ�ŷ�������ҽ��ID��ż����  �Ҽǵ���");
    setFixedSize(350, 200);
    m_Lable = new QLabel(m_strText);
    m_Lable->setAlignment(Qt::AlignCenter);     //������ʾ
    m_Lable->setWordWrap(true);                     //�Զ�����
    if ( type == QMessageBox::Ok)
    {
        m_OkBtn = new DPageBtn(this, "ȷ��", BUTTON_TEXT);
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
        m_CloseBtn = new DPageBtn(this, "ȡ��", BUTTON_TEXT);
        m_OkBtn = new DPageBtn(this, "ȷ��", BUTTON_TEXT);
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

