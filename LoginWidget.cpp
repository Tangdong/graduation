#include "LoginWidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    InitGui();
    m_login_status = false;
}

LoginWidget::~LoginWidget()
{
}

void LoginWidget::ChangeLoginStatus()
{
    m_login_status = false;
}

void LoginWidget::InitGui()
{
    QLabel* namelab = new QLabel("账号:");
    m_nameEdt = new DLineEdit;
    QHBoxLayout* namehbox = new QHBoxLayout;
    namehbox->addStretch();
    namehbox->addWidget(namelab);
    namehbox->addWidget(m_nameEdt);
    namehbox->addStretch();

    QLabel* passlab = new QLabel("密码:");
    m_passEdt = new DLineEdit;

    m_login = new DPageBtn(this, "登录", BUTTON_TEXT);
    m_register = new DPageBtn(this, "注册", BUTTON_TEXT);

    m_nameLb = new QLabel("sucees");
    m_passLb = new QLabel("sucees");

    m_passLb->setAlignment(Qt::AlignCenter);
    m_nameLb->setAlignment(Qt::AlignCenter);

    QHBoxLayout* passhbox = new QHBoxLayout;
    passhbox->addStretch();
    passhbox->addWidget(passlab);
    passhbox->addWidget(m_passEdt);
    passhbox->addStretch();


    QHBoxLayout* btnhbox = new QHBoxLayout;
    btnhbox->addStretch();
    btnhbox->addWidget(m_login);
    btnhbox->addStretch();
    btnhbox->addWidget(m_register);
    btnhbox->addStretch();

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addStretch();
    vbox->addLayout(namehbox);
    vbox->addWidget(m_nameLb);
    vbox->addStretch();
    vbox->addLayout(passhbox);
    vbox->addWidget(m_passLb);
    vbox->addStretch();
    vbox->addLayout(btnhbox);
    vbox->addStretch();

    setFixedSize(450, 350);
    this->setLayout(vbox);
    setAttribute(Qt::WA_DeleteOnClose);//关闭时候执行析构函数

    connect(m_login, SIGNAL(PageBtnClienk()), this, SLOT(OnLoginBtnClick()));
    connect(m_register, SIGNAL(PageBtnClienk()), this, SLOT(OnRegisterBtnClick()));
    m_nameEdt->setText("201706024001");
    m_passEdt->setText("123456");
}

void LoginWidget::OnLoginBtnClick()
{
    if ( m_login_status )
    {
        return ;
    }
    if (m_nameEdt->text().isEmpty())
    {
        m_nameLb->setText(QString("<span style='font-size: 12px; color: rgb(182,191,201);'>%1</span>").arg("用户名不能为空"));
        m_passLb->setText("");

        return;
    }
    if (m_passEdt->text().isEmpty())
    {
        m_nameLb->setText("");
        m_passLb->setText(QString("<span style='font-size: 12px; color: rgb(182,191,201);'>%1</span>").arg("密码不能为空"));
        return;
    }
    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    if (Socket != NULL)
    {
        QString sendmsg = QString("{ \n"
            "\"status\":\"0\",  \n"
            "\"firstmsg\" : \"%1\",\n"
            "\"secondmsg\" : \"%2\", \n"
            "\"thirdmsg\" : \"3\", \n"
            "\"fourthmsg\" :\"4\" };").arg(m_nameEdt->text()).arg(m_passEdt->text());
        Socket->write(sendmsg.toUtf8());
    }
    m_login_status = true;
}

bool LoginWidget::LoginMsg(SocketMsg msg)
{
    bool result = false;
    if (msg.firstmsg == "LOGIN_OK")
    {
        close();
        result = true;
    }

    if (msg.firstmsg == "LOGIN_ON")
    {
        m_nameLb->setText(QString("<span style='font-size: 12px; color: rgb(182,191,201);'>%1</span>").arg("该用户已经登录"));
        m_passLb->setText("");
    }
    if (msg.firstmsg == "USER_NOT_EXIST")
    {
        m_nameLb->setText(QString("<span style='font-size: 12px; color: rgb(182,191,201);'>%1</span>").arg("用户名或密码错误"));
        m_passLb->setText(QString("<span style='font-size: 12px; color: rgb(182,191,201);'>%1</span>").arg("用户名或密码错误"));
    }
    if (msg.firstmsg == "LOGIN_REPEAT")
    {
        m_nameLb->setText(QString("<span style='font-size: 12px; color: rgb(182,191,201);'>%1</span>").arg("用户名已登录"));
        m_passLb->setText(QString("<span style='font-size: 12px; color: rgb(182,191,201);'>%1</span>").arg("用户名已登录"));
    }
    
    m_login_status = false;
    return result;
}

void LoginWidget::RegisterMsg(SocketMsg msg)
{
    if (msg.firstmsg == "REGISTER_FAIL")
    {
        qDebug() << "REGISTER_FAIL";
    }

    if (msg.firstmsg == "REGISTER_OK")
    {
        qDebug() << "REGISTER_OK";
        m_register->close();
        this->show();
    }
}

void LoginWidget::OnRegisterBtnClick()
{
    RegisterWidget* regwgt = new RegisterWidget;
    regwgt->show();
    this->setHidden(true);
    connect(regwgt, SIGNAL(SigLoginWidgetShow()), this, SLOT(show()));
}

