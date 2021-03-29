#include "ModifyInterface.h"

ModifyInterface::ModifyInterface(QWidget *parent)
    : QWidget(parent)
{
    InitGui();
}

ModifyInterface::~ModifyInterface()
{
}

void  ModifyInterface::InitGui()
{
    m_UserNum = new QLabel("账号：");
    m_UserName = new QLabel("姓名：");
    m_UserSex = new QLabel("性别：");
    m_Telephone = new QLabel("电话：");
    m_Department = new QLabel("院系：");
    m_Speciality = new QLabel("专业：");
    m_Modify = new DPageBtn(this, "修改");
    m_Ok = new DPageBtn(this, "确定");

    m_UserNumLd = new DLineEdit(this,false);
    m_UserNameLd = new DLineEdit(this, false);
    m_UserSexLd = new DLineEdit(this, false);
    m_TelephoneLd = new DLineEdit(this, false);
    m_DepartmentLd = new DLineEdit(this, false);
    m_SpecialityLd = new DLineEdit(this, false);

    QHBoxLayout* NumHbox = new QHBoxLayout;
    NumHbox->addWidget(m_UserNum);
    NumHbox->addWidget(m_UserNumLd);
    NumHbox->setSpacing(30);
    QHBoxLayout* NameHbox = new QHBoxLayout;
    NameHbox->addWidget(m_UserName);
    NameHbox->addWidget(m_UserNameLd);
    NameHbox->setSpacing(30);
    QHBoxLayout* SexHbox = new QHBoxLayout;
    SexHbox->addWidget(m_UserSex);
    SexHbox->addWidget(m_UserSexLd);
    SexHbox->setSpacing(30);
    QHBoxLayout* TelephoneHbox = new QHBoxLayout;
    TelephoneHbox->addWidget(m_Telephone);
    TelephoneHbox->addWidget(m_TelephoneLd);
    TelephoneHbox->setSpacing(30);
    QHBoxLayout* DepartmentHbox = new QHBoxLayout;
    DepartmentHbox->addWidget(m_Department);
    DepartmentHbox->addWidget(m_DepartmentLd);
    DepartmentHbox->setSpacing(30);
    QHBoxLayout* SpecialityHbox = new QHBoxLayout;
    SpecialityHbox->addWidget(m_Speciality);
    SpecialityHbox->addWidget(m_SpecialityLd);
    SpecialityHbox->setSpacing(30);

    QHBoxLayout* lineHbox1 = new QHBoxLayout;
    lineHbox1->addLayout(NumHbox);
    lineHbox1->addLayout(NameHbox);
    lineHbox1->setSpacing(50);
    QHBoxLayout* lineHbox2 = new QHBoxLayout;
    lineHbox2->addLayout(SexHbox);
    lineHbox2->addLayout(TelephoneHbox);
    lineHbox2->setSpacing(50);
    QHBoxLayout* lineHbox3 = new QHBoxLayout;
    lineHbox3->addLayout(DepartmentHbox);
    lineHbox3->addLayout(SpecialityHbox);
    lineHbox3->setSpacing(50);

    QHBoxLayout *lineHbox4 = new QHBoxLayout;
    lineHbox4->addWidget(m_Modify);
    lineHbox4->addWidget(m_Ok);

    QVBoxLayout *layVbox = new QVBoxLayout;
    layVbox->addLayout(lineHbox1);
    layVbox->addLayout(lineHbox2);
    layVbox->addLayout(lineHbox3);
    layVbox->addLayout(lineHbox4);
    layVbox->setContentsMargins(50, 20, 50, 30);
    setLayout(layVbox);
    connect(m_Modify, SIGNAL(PageBtnClienk()), this, SLOT(OnModifyBtnClick()));
    connect(m_Ok, SIGNAL(PageBtnClienk()), this, SLOT(OnOkBtnClick()));
}


void ModifyInterface::ModifyMsg(SocketMsg msg)
{
    if (msg.firstmsg == "MODIFY_ERROR")
    {
        qDebug() << "修改信息失败";
        return;
    }
    if (msg.firstmsg == "MODIFY_OK")
    {
        qDebug() << "修改信息成功";
        return;
    }
    if (g_userinfo == NULL)
    {
        g_userinfo = new Userinfo;
    }
    QStringList listmsg;

    QStringList list = msg.firstmsg.split("-");
    g_userinfo->usernum = list[0];
    g_userinfo->password = list[1];

    list.clear();
    list = msg.secondmsg.split("-");
    if (list[0].toInt() == 0)
    {
        g_userinfo->admin = false;
    }
    else
    {
        g_userinfo->admin = true;
    }

    g_userinfo->borrownum = list[1].toInt();

    if (list[2].toInt() == 0)
    {
        g_userinfo->reportloss = false;
    }
    else
    {
        g_userinfo->reportloss = true;
    }

    list.clear();
    list = msg.thirdmsg.split("-");
    g_userinfo->username = list[0];
    g_userinfo->sex = list[1];
    g_userinfo->telephone = list[2];

    list.clear();
    list = msg.fourthmsg.split("-");
    g_userinfo->department = list[0];
    g_userinfo->speciality = list[1];

    emit SigUserInfoUpdate();
    SetInfomation();
}
void  ModifyInterface::SetInfomation()
{
    m_UserNumLd->setText(g_userinfo->usernum);
    m_UserNameLd->setText(g_userinfo->username);
    m_UserSexLd->setText(g_userinfo->sex);
    m_TelephoneLd->setText(g_userinfo->telephone);
    m_DepartmentLd->setText(g_userinfo->department);
    m_SpecialityLd->setText(g_userinfo->speciality);
}
void  ModifyInterface::OnOkBtnClick()
{
    //m_UserNumLd->setReadOnly(true);
    m_UserNameLd->setReadOnly(true);
    m_UserSexLd->setReadOnly(true);
    m_TelephoneLd->setReadOnly(true);
    m_DepartmentLd->setReadOnly(true);
    m_SpecialityLd->setReadOnly(true);

    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    if (Socket != NULL)
    {
        QString sendmsg = QString("{ \n"
            "\"status\":\"4\",  \n"
            "\"firstmsg\" : \"%1\",\n"
            "\"secondmsg\" : \"%2-%3\", \n"
            "\"thirdmsg\" : \"%4-%5\", \n"
            "\"fourthmsg\" :\"%6\" };").arg(m_UserNumLd->text()).arg(m_UserNameLd->text()).arg(m_UserSexLd->text())
            .arg(m_TelephoneLd->text()).arg(m_DepartmentLd->text()).arg(m_SpecialityLd->text());
        Socket->write(sendmsg.toUtf8());
    }
}

void  ModifyInterface::OnModifyBtnClick()
{
    //m_UserNumLd->setReadOnly(false);
    m_UserNameLd->setReadOnly(false);
    m_UserSexLd->setReadOnly(false);
    m_TelephoneLd->setReadOnly(false);
    m_DepartmentLd->setReadOnly(false);
    m_SpecialityLd->setReadOnly(false);
}
