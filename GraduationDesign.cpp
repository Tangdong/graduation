#include "GraduationDesign.h"
#include "DialogWidget.h"

GraduationDesign::GraduationDesign(QWidget* parent)
    : QWidget(parent)
{
    g_Graduation = NULL;
    g_Socket = NULL;
    g_userinfo = NULL;
    //可以添加一个初始化页面
    InitGui();
#if 1
    InitNetWork();
    m_BookManageBtn->setHidden(false);
    this->setHidden(true);
    m_Login = new LoginWidget;
    m_Login->show();
#endif
    connect(m_Modify, SIGNAL(SigUserInfoUpdate()), this, SLOT(UpdateUserInfo()));
    connect(m_Borrow, SIGNAL(SigUserInfoUpdate()), this, SLOT(UpdateUserInfo()));
    connect(m_Return, SIGNAL(SigUserInfoUpdate()), this, SLOT(UpdateUserInfo()));

    //获取程序当前运行目录
    QString fileName = QCoreApplication::applicationDirPath();

}

void GraduationDesign::InitGui()
{
    ui.setupUi(this);
    resize(1000, 750);
    m_stackwidget = new QStackedWidget;

    m_BorrowBtn = new DPageBtn(this, "借阅", BUTTON_HOME);
    m_ReturnBtn = new DPageBtn(this, "归还", BUTTON_HOME);
    m_ModifyBtn = new DPageBtn(this, "个人信息", BUTTON_HOME);
    m_ViewInfoBtn = new DPageBtn(this, "借阅记录", BUTTON_HOME);
    m_SettingBtn = new DPageBtn(this, "设置", BUTTON_HOME);
    m_BookManageBtn = new DPageBtn(this, "书籍管理", BUTTON_HOME);

    m_Borrow = new BorrowInterface;
    m_Return = new ReturnInterface;
    m_Modify = new ModifyInterface;
    m_ViewInfo = new ViewInformation;
    m_Setting = new SettingInterface;
    m_BookManage = new BookManagement;

    int id = 0;
    id = m_stackwidget->addWidget(m_Borrow);
    m_mapStackWgt.insert(std::pair<int, QWidget*>(id, m_Borrow));
    m_BorrowBtn->SetId(id);
    id = m_stackwidget->addWidget(m_Return);
    m_mapStackWgt.insert(std::pair<int, QWidget*>(id, m_Return));
    m_ReturnBtn->SetId(id);
    id = m_stackwidget->addWidget(m_Modify);
    m_mapStackWgt.insert(std::pair<int, QWidget*>(id, m_Modify));
    m_ModifyBtn->SetId(id);
    id = m_stackwidget->addWidget(m_ViewInfo);
    m_mapStackWgt.insert(std::pair<int, QWidget*>(id, m_ViewInfo));
    m_ViewInfoBtn->SetId(id);
    id = m_stackwidget->addWidget(m_Setting);
    m_mapStackWgt.insert(std::pair<int, QWidget*>(id, m_Setting));
    m_SettingBtn->SetId(id);
    id = m_stackwidget->addWidget(m_BookManage);
    m_mapStackWgt.insert(std::pair<int, QWidget*>(id, m_BookManage));
    m_BookManageBtn->SetId(id);

    QHBoxLayout* layHbox = new QHBoxLayout;
    layHbox->addWidget(m_BorrowBtn);
    layHbox->addWidget(m_ReturnBtn);
    layHbox->addWidget(m_ModifyBtn);
    layHbox->addWidget(m_ViewInfoBtn);
    layHbox->addWidget(m_SettingBtn);
    layHbox->addWidget(m_BookManageBtn);

    QVBoxLayout* layVbox = new QVBoxLayout;
    layVbox->addLayout(layHbox);
    layVbox->addWidget(m_stackwidget);
    setLayout(layVbox);
    connect(m_BorrowBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnPageBtnClienk()));
    connect(m_ReturnBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnPageBtnClienk()));
    connect(m_ModifyBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnPageBtnClienk()));
    connect(m_ViewInfoBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnPageBtnClienk()));
    connect(m_SettingBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnPageBtnClienk()));
    connect(m_BookManageBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnPageBtnClienk()));
    //connect(m_BookManageBtn, SIGNAL(PageBtnClienk()), this, SLOT(TestMessageBox()));

    g_Graduation = this;
}

void GraduationDesign::OnPageBtnClienk()
{
    DPageBtn* pbtn = qobject_cast<DPageBtn *>(sender());
    m_BorrowBtn->SetDown(false);
    m_ReturnBtn->SetDown(false);
    m_ModifyBtn->SetDown(false);
    m_ViewInfoBtn->SetDown(false);
    m_SettingBtn->SetDown(false);
    m_BookManageBtn->SetDown(false);
    if (NULL != pbtn)
    {
        pbtn->SetDown(true);
        int id = pbtn->GetId();
        std::map<int, QWidget*>::iterator it = m_mapStackWgt.find(id);
        m_stackwidget->setCurrentWidget(it->second);
        if (it->second == m_Return )
        {
            m_Return->SetTableData();
        }
        if (it->second == m_ViewInfo)
        {
            m_ViewInfo->SetTableData();
        }
    }
}

void GraduationDesign::InitNetWork()
{
    m_Socket = new QTcpSocket;
    connect(m_Socket, SIGNAL(readyRead()), this, SLOT(RecvSocketMsg()));
    connect(m_Socket, SIGNAL(disconnected()), this, SLOT(DisConnect()));
    connect(m_Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ErrorConnect()));
    connect(m_Socket, SIGNAL(connected()), this, SLOT(Connected()));
#if 1
    m_Socket->connectToHost("192.168.206.235", 8888);
#else
    m_Socket->connectToHost("8.129.87.21", 8080);
    //m_Socket->connectToHost("127.0.0.1", 8080);
#endif
}

BorrowInterface* GraduationDesign::GetBorrowInterface()
{
    return m_Borrow;
}
ReturnInterface* GraduationDesign::GetReturnInterface()
{
    return m_Return;
}
ModifyInterface* GraduationDesign::GetModifyInterface()
{
    return m_Modify;
}
ViewInformation* GraduationDesign::GetViewInformation()
{
    return m_ViewInfo;
}
SettingInterface* GraduationDesign::GetSettingInterface()
{
    return m_Setting;
}
BookManagement* GraduationDesign::GetBookManagement()
{
    return m_BookManage;
}

void GraduationDesign::TestMessageBox()
{
    //DMessageBox* box = new DMessageBox(QMessageBox::Ok | QMessageBox::Cancel);
    //int ret = box->exec();
    //if ( ret == QMessageBox::Ok)
    //{
    //    //点击确认出现
    //}
    //GraduationDesign* Grd = (GraduationDesign*)g_Graduation;
    //SettingInterface *Set = Grd->GetSettingInterface();
    //if ( Set != NULL)
    //{
    //    if ( Set == m_Setting)
    //    {
    //        qDebug() << "lvoe";
    //    }
    //}
//     RegisterWidget* reg = new RegisterWidget;
//     reg->show();

    DDialog *Dialog = new DDialog(360, 200, this);
    Dialog->setTitleName("Rename");  //Rename
    DialogWidget *dig = new DialogWidget(Dialog);
    //dig->SetShowLb("hello world!", "rgb(255,128,0)");
    dig->SetShowLb("hello world!", "red");
    Dialog->setContentWidget(dig);
    connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
    Dialog->exec();

}

void GraduationDesign::RecvSocketMsg()
{
    QByteArray  allData = m_Socket->readAll();
    QString msgData = QString::fromUtf8(allData);
    if ( !m_Errormsg.isEmpty())
    {
        msgData = m_Errormsg + msgData;
        m_Errormsg.clear();
    }
    QStringList msgdatalist = msgData.split(";");
    qDebug() << allData;

    for (int i = 0; i < msgdatalist.size();i++)
    {
        if ( msgdatalist.at(i).isEmpty())
        {
            continue;
        }
        QJsonParseError jsonError;//Qt5新类
        QJsonDocument json(QJsonDocument::fromJson(msgdatalist.at(i).toUtf8(), &jsonError));//Qt5新类
        SocketMsg msg;
        if (jsonError.error == QJsonParseError::NoError)
        {
            if (json.isObject())
            {
                //开始解析json对象
                QJsonObject obj = json.object();
                //如果包含id
                if (obj.contains("status"))
                {
                    QJsonValue name_value = obj.take("status");
                    if (name_value.isString())
                    {
                        msg.status = name_value.toVariant().toString().toInt();
                    }
                }
                if (obj.contains("firstmsg"))
                {
                    QJsonValue usernum_value = obj.take("firstmsg");
                    msg.firstmsg = QString::fromLocal8Bit(usernum_value.toVariant().toString().toLocal8Bit());
                }
                if (obj.contains("secondmsg"))
                {
                    QJsonValue usernum_value = obj.take("secondmsg");
                    //msg.secondmsg = usernum_value.toVariant().toString();
                    msg.secondmsg = QString::fromLocal8Bit(usernum_value.toVariant().toString().toLocal8Bit());

                }
                if (obj.contains("thirdmsg"))
                {
                    QJsonValue usernum_value = obj.take("thirdmsg");
                    msg.thirdmsg = usernum_value.toVariant().toString();
                }
                if (obj.contains("fourthmsg"))
                {
                    QJsonValue usernum_value = obj.take("fourthmsg");
                    msg.fourthmsg = usernum_value.toVariant().toString();
                }
            }
        }
        else
        {
            qDebug() << "Json error!!";
            m_Errormsg = msgdatalist[i];
            QTcpSocket* Socket = (QTcpSocket*)g_Socket;
            QString sendmsg = QString("{ \n"
                "\"status\":\"12\",  \n"
                "\"firstmsg\" : \"1\",\n"
                "\"secondmsg\" : \"2\", \n"
                "\"thirdmsg\" : \"3\", \n"
                "\"fourthmsg\" :\"4\" };");
            Socket->write(sendmsg.toUtf8());

            continue;
        }
        // QJsonObject obj = json.object();
        // QString str = obj.take("id").toVariant().toString();
        qDebug() << "msg.status = " << msg.status;
        qDebug() << "msg.firstmsg = " << msg.firstmsg;
        qDebug() << "msg.secondmsg = " << msg.secondmsg;
        qDebug() << "msg.thirdmsg = " << msg.thirdmsg;
        qDebug() << "msg.fourthmsg = " << msg.fourthmsg;

        //DLFUNC::GetIndexText(10001);

        switch (msg.status)
        {
        case LOGIN:
            if (m_Login->LoginMsg(msg))
            {
                this->show();
            }
            break;
        case REGISTER:
            m_Login->RegisterMsg(msg);
            break;
        case BORROW:
            m_Borrow->BorrowMsg(msg);
            break;
        case RETURN:
            m_Return->ReturnMsg(msg);
            break;
        case INFORMATION:
            m_Modify->ModifyMsg(msg);
            break;
        case VIEWINFO:
            m_ViewInfo->ViewInfoMsg(msg);
            break;
        case SETTING:
            m_Setting->SettingMsg(msg);
            break;
        case BOOKINFO:
            m_BookManage->BookManageMsg(msg);
            break;
        case SAVEBOOK:
            SaveBook(msg);
            break;
        case CHANGEPASSWORD:
            m_Setting->SettingMsg(msg);
        default:
            break;
        }
    }
}

void GraduationDesign::DisConnect()
{
    qDebug() << "server disconnect";
    //delete m_Socket;
}

void GraduationDesign::ErrorConnect()
{
    //delete m_Socket;
    DDialog *Dialog;
    if (this->isHidden())
    {
        Dialog = new DDialog(360, 200, m_Login);
    }
    else
    {
        Dialog = new DDialog(360, 200, this);
    }
    Dialog->setTitleName("Rename");  //Rename
    DialogWidget *dig = new DialogWidget(Dialog);
    //dig->SetShowLb("hello world!", "rgb(255,128,0)");
    dig->SetShowLb("server ErrorConnect || 连接出错请检查网络设置", "red");
    Dialog->setContentWidget(dig);
    connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
    Dialog->exec();
}

void GraduationDesign::Connected()
{
    qDebug() << "connected;";
    g_Socket = m_Socket;
}

void GraduationDesign::UpdateUserInfo()
{
    m_Borrow->UpdateUserInfo();
    m_Return->UpdateUserInfo();
    m_ViewInfo->UpdateUserInfo();
}

void GraduationDesign::SetSaveBookinfo(Bookinfo book)
{
    m_BookinfoVector.push_back(book);
}
void GraduationDesign::SaveBook(SocketMsg msg)
{
    Bookinfo bookmsg;
    //num-bookname    autor-类别-出版社   可借-在管 处理人-入馆时间
    QStringList list = msg.firstmsg.split("-");
    bookmsg.booknum = list[0];
    bookmsg.bookname = list[1];

    list.clear();
    list = msg.secondmsg.split("-");
    bookmsg.author = list[0];
    bookmsg.catagory = list[1];
    bookmsg.publisher = list[2];

    list.clear();
    list = msg.thirdmsg.split("-");
    bookmsg.totalinventory = list[0].toInt();
    bookmsg.totalavailable = list[1].toInt();

    list.clear();
    list = msg.fourthmsg.split("-");
    bookmsg.entertime = list[1].toULong();
    
    m_BookinfoVector.push_back(bookmsg);
}

void GraduationDesign::DeleteBookinfoItem(QString booknum)
{
    std::vector<Bookinfo>::iterator it2 = m_BookinfoVector.begin();
    for (; it2 != m_BookinfoVector.end(); it2++)
    {
        if (it2->booknum == booknum)
        {
            m_BookinfoVector.erase(it2);
            break;
        }
    }
}

Bookinfo GraduationDesign::GetSaveBook(QString booknum)
{
    for (int i = 0; i < m_BookinfoVector.size(); i++)
    {
        if (m_BookinfoVector[i].booknum == booknum)
        {
            return m_BookinfoVector[i];
        }
    }
    Bookinfo book;
    book.totalinventory = -1;
    return book;
}

std::vector<Bookinfo> GraduationDesign::GetSaveBookVector()
{
    return m_BookinfoVector;
}
