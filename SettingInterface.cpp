#include "SettingInterface.h"

SettingInterface::SettingInterface(QWidget *parent)
    : QWidget(parent)
{
    InitGui();
}

SettingInterface::~SettingInterface()
{
}

void SettingInterface::InitGui()
{
    m_ModifyPass = new DPageBtn(this, "修改密码");
    QHBoxLayout* layHbox = new QHBoxLayout;
    layHbox->addWidget(m_ModifyPass);
    layHbox->addStretch();
    setLayout(layHbox);
    connect(m_ModifyPass, SIGNAL(PageBtnClienk()), this, SLOT(OnModifyPassBtnClick()));

}
void SettingInterface::SettingMsg(SocketMsg msg)
{
    if (msg.status == CHANGEPASSWORD)
    {
        ChangePasswordResult(msg);
    }
    //CHANGEPASSWORD_FAIL

}

void SettingInterface::ChangePasswordResult(SocketMsg msg)
{
    DDialog *Dialog = new DDialog(360, 200, this);
    Dialog->setTitleName("Rename");  //Rename
    DialogWidget *dig = new DialogWidget(Dialog);
    if (msg.firstmsg == "CHANGEPASSWORD_FAIL")
    {
        dig->SetShowLb("修改密码失败请和管理员联系", "red");
    }
    else
    {
        dig->SetShowLb("密码修改成功", "green");
        g_userinfo->password = msg.secondmsg;
    }
    Dialog->setContentWidget(dig);
    connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
    Dialog->exec();
}

void SettingInterface::OnModifyPassBtnClick()
{
    DDialog* Dialog = new DDialog(600, 400, this);
    ChangePasswd* ChangeNameWgt = new ChangePasswd(Dialog);
    Dialog->setContentWidget(ChangeNameWgt);
    connect(Dialog, SIGNAL(sigCloseDlg()), ChangeNameWgt, SLOT(onCloseDlg()));
    Dialog->exec();
}