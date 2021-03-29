#include "DialogWidget.h"

DialogWidget::DialogWidget(DDialog *parent)
    : QWidget(parent)
{
    m_parent = parent;
    m_tiplb = new QLabel("hello");
    m_okBtn = new QPushButton("OK");

    m_tiplb->setWordWrap(true);
    m_tiplb->setFixedWidth(200);
    m_tiplb->setAlignment(Qt::AlignCenter);

    m_okBtn->setFixedSize(80, 30);

    QString qssBtnInLoginWel = "QPushButton{font-size:14px;}\
                               QPushButton:enabled{color: white; border: none;border-style:none; background: rgb(51, 146, 255;)}\
                               :enabled:hover{background: rgb(18, 120, 237)}\
                               :enabled:pressed{background: rgb(18, 110, 215)}\
                               :!enabled{color: white;border: none;background: rgb(186, 186, 186)}\
                               QPushButton:focus{outline: none;}";
    m_okBtn->setStyleSheet(qssBtnInLoginWel);

    QHBoxLayout *lbhbox = new QHBoxLayout;
    lbhbox->addWidget(m_tiplb);

    QHBoxLayout *btnhbox = new QHBoxLayout;
    btnhbox->addWidget(m_okBtn);
    btnhbox->setAlignment(Qt::AlignCenter);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(lbhbox);
    //vbox->addSpacing(20);
    vbox->addStretch();
    vbox->addLayout(btnhbox);
    vbox->setContentsMargins(0, 50, 0, 30);
    setLayout(vbox);
    connect(m_okBtn, SIGNAL(clicked()), this, SLOT(onOkClicked()));

}

DialogWidget::~DialogWidget()
{
}

void DialogWidget::onOkClicked()
{
    m_parent->done(false);
}

void DialogWidget::onCloseDlg()
{
    m_parent->done(false);
}
void DialogWidget::SetShowLb(QString text, QString color)
{
    m_tiplb->setText(text);
    setStyleSheet(QString("color:%1").arg(color));
}