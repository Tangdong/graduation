#include "ChangePasswd.h"
#include "GraduationDesign.h"


ChangePasswd::ChangePasswd(DDialog *parent)
    : QWidget(parent)
{
    m_parent = parent;
    m_oldpassedt = new QLineEdit;
    m_passedt = new QLineEdit;
    m_newpassedt = new QLineEdit;
    m_oldpasslb = new QLabel("旧密码：");
    m_passlb = new QLabel("新密码：");
    m_newpasslb = new QLabel("确认密码：");
    m_tiplb = new QLabel("error");
    m_cancelBtn = new QPushButton;
    m_okBtn = new QPushButton;

    m_SpecialCharlist << "\\" << "/" << "|" << ":" << "?" << "*" << "\"" << "<" << ">" << "-" << "&";

    m_cancelBtn->setText("Cancel"); //Cancel
    m_okBtn->setText("OK"); //OK
    QString qssBorderBtn = "QPushButton:enabled{font:14px;color:rgb(88,91,95); border: 1px solid rgb(191,199,208); background: rgb(255, 255, 255)}\
                           :enabled:hover{font:14px;color:rgb(51,146,255);border:1px solid rgb(51,146,255);background: rgb(255, 255, 255)}\
                           :enabled:pressed{font:14px;color:rgb(19,110,215);border:1px solid rgb(19,110,215);background: rgb(255, 255, 255)}\
                           :!enabled{font:14px;color:rgb(176,177,178);border:1px solid rgb(236,238,241);background: rgb(255, 255, 255)}\
                           QPushButton:focus{outline: none;}";

    QString qssBtnInLoginWel = "QPushButton{font-size:14px;}\
                               QPushButton:enabled{color: white; border: none;border-style:none; background: rgb(51, 146, 255;)}\
                               :enabled:hover{background: rgb(18, 120, 237)}\
                               :enabled:pressed{background: rgb(18, 110, 215)}\
                               :!enabled{color: white;border: none;background: rgb(186, 186, 186)}\
                               QPushButton:focus{outline: none;}";

    m_cancelBtn->setStyleSheet(qssBorderBtn);
    m_cancelBtn->setFixedSize(120, 40);
    m_okBtn->setStyleSheet(qssBtnInLoginWel);
    m_okBtn->setFixedSize(120, 40);
    m_tiplb->setStyleSheet("color:red");
    m_passedt->setStyleSheet("QLineEdit{border: 1px solid rgb(182,191,201); font-size: 12px;}QLineEdit:hover{border: 1px solid rgb(51,146,255);}");
    m_newpassedt->setStyleSheet("QLineEdit{border: 1px solid rgb(182,191,201); font-size: 12px;}QLineEdit:hover{border: 1px solid rgb(51,146,255);}");
    m_oldpassedt->setFixedHeight(50);
    m_passedt->setFixedHeight(50);
    m_newpassedt->setFixedHeight(50);

    QHBoxLayout  *oldpasshbox = new QHBoxLayout;
    oldpasshbox->addWidget(m_oldpasslb);
    oldpasshbox->addWidget(m_oldpassedt);

    QHBoxLayout  *passhbox = new QHBoxLayout;
    passhbox->addWidget(m_passlb);
    passhbox->addWidget(m_passedt);

    QHBoxLayout  *newpasshbox = new QHBoxLayout;
    newpasshbox->addWidget(m_newpasslb);
    newpasshbox->addWidget(m_newpassedt);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addStretch();
    vbox->addLayout(oldpasshbox);
    vbox->addSpacing(10);
    vbox->addLayout(passhbox);
    vbox->addSpacing(10);
    vbox->addLayout(newpasshbox);
    vbox->addSpacing(10);
    vbox->addWidget(m_tiplb);
    vbox->addStretch();
    vbox->setContentsMargins(0, 0, 0,0 );

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addStretch();
    hbox->addWidget(m_cancelBtn);
    hbox->addSpacing(10);
    hbox->addWidget(m_okBtn);

    QVBoxLayout *vboxlay = new QVBoxLayout;
    vboxlay->addLayout(vbox);
    vboxlay->addLayout(hbox);
    vboxlay->setContentsMargins(50, 30, 30, 20);

    connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    connect(m_okBtn, SIGNAL(clicked()), this, SLOT(onOkClicked()));
    //connect(m_lineedit, SIGNAL(textEdited(const QString &)), this, SLOT(onChangeLineEdit(const QString &)));
    setLayout(vboxlay);
}

ChangePasswd::~ChangePasswd()
{
}


void ChangePasswd::onChangeLineEdit(const QString &text)
{
    if (text.isEmpty())
    {
        m_okBtn->setDisabled(true);
        m_tiplb->setText("");

        return;
    }
    for (int i = 0; i < m_SpecialCharlist.size(); i++)
    {
        if (text.contains(m_SpecialCharlist.at(i)))
        {
            m_tiplb->setText("The cloud drive name cannot include these characters : / \\ | : * ? < > - &.");
            m_okBtn->setDisabled(true);
            return ;
        }
    }
    m_tiplb->setText("succes");
    m_okBtn->setDisabled(false);
}

void ChangePasswd::onCancelClicked()
{
    m_parent->done(false);
}

void ChangePasswd::onOkClicked()
{
    QString oldpass = m_oldpassedt->text();
    QString pass    = m_passedt->text();
    QString newpass = m_newpassedt->text();

    if (pass != newpass)
    {
        m_tiplb->setText("两次输入的密码不一致请重新输入！");
        return;
    }

    for (int i = 0; i < m_SpecialCharlist.size(); i++)
    {
        if (pass.contains(m_SpecialCharlist.at(i)))
        {
            m_tiplb->setText("The cloud drive name cannot include these characters : / \\ | : * ? < > - &.");
            return;
        }
    }
    if (oldpass != g_userinfo->password)
    {
        m_tiplb->setText("旧密码错误，请重新输入！");
        return;
    }
    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    QString sendmsg = QString("{ \n"
        "\"status\":\"11\",  \n"
        "\"firstmsg\" : \"%1\",\n"
        "\"secondmsg\" : \"%2\", \n"
        "\"thirdmsg\" : \"3\", \n"
        "\"fourthmsg\" :\"4\" };").arg(g_userinfo->usernum).arg(pass);
    Socket->write(sendmsg.toUtf8());
    m_parent->done(true);
}

void ChangePasswd::onCloseDlg()
{
    m_parent->done(false);
}