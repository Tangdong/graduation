#include "RegisterWidget.h"

RegisterWidget::RegisterWidget(QWidget *parent)
    : QWidget(parent)
{
    InitGui();
}

RegisterWidget::~RegisterWidget()
{
}


void RegisterWidget::InitGui()
{
    m_UserNum = new QLabel("�˺ţ�");
    m_UserName = new QLabel("������");
    m_UserSex = new QLabel("�Ա�");
    m_Telephone = new QLabel("�绰��");
    m_Department = new QLabel("Ժϵ��");
    m_Speciality = new QLabel("רҵ��");
    m_PassWord = new QLabel("���룺");
    m_ConfirmPass = new QLabel("ȷ�����룺");

    m_UserNumLd = new DLineEdit;
    m_UserNameLd = new DLineEdit;
    m_UserSexLd = new DLineEdit;
    m_TelephoneLd = new DLineEdit;
    m_DepartmentLd = new DLineEdit;
    m_SpecialityLd = new DLineEdit;
    m_PassWordLd = new DLineEdit;
    m_ConfirmPassLd = new DLineEdit;

    m_Ok = new DPageBtn(this, " ȷ��", BUTTON_TEXT);
    m_Cancel = new DPageBtn(this, "ȡ��", BUTTON_TEXT);

    QHBoxLayout* NumHbox = new QHBoxLayout;
    NumHbox->addWidget(m_UserNum);
    NumHbox->addWidget(m_UserNumLd);
    //NumHbox->setSpacing(30);

    QHBoxLayout *passhbox = new QHBoxLayout;
    passhbox->addWidget(m_PassWord);
    passhbox->addWidget(m_PassWordLd);

    QHBoxLayout *ConfirmPasshbox = new QHBoxLayout;
    ConfirmPasshbox->addWidget(m_ConfirmPass);
    ConfirmPasshbox->addWidget(m_ConfirmPassLd);

    QHBoxLayout* NameHbox = new QHBoxLayout;
    NameHbox->addWidget(m_UserName);
    NameHbox->addWidget(m_UserNameLd);
    //NameHbox->setSpacing(30);
    QHBoxLayout* SexHbox = new QHBoxLayout;
    SexHbox->addWidget(m_UserSex);
    SexHbox->addWidget(m_UserSexLd);
    SexHbox->setSpacing(30);
    QHBoxLayout* TelephoneHbox = new QHBoxLayout;
    TelephoneHbox->addWidget(m_Telephone);
    TelephoneHbox->addWidget(m_TelephoneLd);
    //TelephoneHbox->setSpacing(30);
    QHBoxLayout* DepartmentHbox = new QHBoxLayout;
    DepartmentHbox->addWidget(m_Department);
    DepartmentHbox->addWidget(m_DepartmentLd);
    //DepartmentHbox->setSpacing(30);
    QHBoxLayout* SpecialityHbox = new QHBoxLayout;
    SpecialityHbox->addWidget(m_Speciality);
    SpecialityHbox->addWidget(m_SpecialityLd);
    //SpecialityHbox->setSpacing(30);

    QHBoxLayout* btnHbox = new QHBoxLayout;
    btnHbox->addWidget(m_Ok);
    btnHbox->addStretch();
    btnHbox->addWidget(m_Cancel);
    btnHbox->setContentsMargins(20, 0, 20, 10);

    QVBoxLayout* Vbox = new QVBoxLayout;
    Vbox->addLayout(NumHbox);
    Vbox->addLayout(passhbox);
    Vbox->addLayout(ConfirmPasshbox);
    Vbox->addLayout(NameHbox);
    Vbox->addLayout(SexHbox);
    Vbox->addLayout(TelephoneHbox);
    Vbox->addLayout(DepartmentHbox);
    Vbox->addLayout(SpecialityHbox);
    Vbox->addLayout(btnHbox);
    Vbox->setContentsMargins(80, 10, 80, 10);
    setFixedSize(500, 600);
    setLayout(Vbox);
    setAttribute(Qt::WA_DeleteOnClose);//�ر�ʱ��ִ����������

    connect(m_Ok, SIGNAL(PageBtnClienk()), this, SLOT(OnOkBtnClick()));
    connect(m_Cancel, SIGNAL(PageBtnClienk()), this, SLOT(OnCancelBtnClick()));


    m_UserNumLd->setText("201706024003");
    m_UserNameLd->setText("С��");
    m_PassWordLd->setText("123456");
    m_ConfirmPassLd->setText("123456");
    m_UserSexLd->setText("��");
    m_TelephoneLd->setText("17325245813");
    m_DepartmentLd->setText("��е����ѧԺ");
    m_SpecialityLd->setText("��е���ӹ���");
}


void RegisterWidget::OnOkBtnClick()
{
    //return;
    //�����������ע������
    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    if (Socket != NULL)
    {
        QString sendmsg = QString("{ \n"
            "\"status\":\"1\",  \n"
            "\"firstmsg\" : \"%1-%2\",\n"
            "\"secondmsg\" : \"%3-%4\", \n"
            "\"thirdmsg\" : \"%5-%6\", \n"
            "\"fourthmsg\" :\"%7-%8\" };").arg(m_UserNumLd->text()).arg(m_UserNameLd->text())
                                  .arg(m_PassWordLd->text()).arg(m_ConfirmPassLd->text())
                                  .arg(m_UserSexLd->text()).arg(m_TelephoneLd->text())
                                  .arg(m_DepartmentLd->text()).arg(m_SpecialityLd->text());
        Socket->write(sendmsg.toUtf8());
    }
}

void RegisterWidget::OnCancelBtnClick()
{
    this->close();
    emit SigLoginWidgetShow();
}
