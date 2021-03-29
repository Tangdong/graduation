#include "BookManagement.h"

BookManagement::BookManagement(QWidget *parent)
    : QWidget(parent)
{
    InitGui();
}

BookManagement::~BookManagement()
{
}

void BookManagement::InitGui()
{
    m_BookNum = new QLabel("书籍编号：");
    m_BookName = new QLabel("书籍名称：");
    m_Author = new QLabel("作者：");
    m_Category = new QLabel("类别：");
    m_Publisher = new QLabel("出版社：");
    m_Totalinventory = new QLabel("库存总量：");
    m_Totalavailable = new QLabel("现存总量：");
    m_Dealpeople = new QLabel("处理人：");

    m_BookNumLd = new DLineEdit;
    m_BookNameLd = new DLineEdit;
    m_AuthorLd = new DLineEdit;
    m_CategoryLd = new DLineEdit;
    m_PublisherLd = new DLineEdit;
    m_TotalinventoryLd = new DLineEdit;
    m_TotalavailableLd = new DLineEdit;
    m_DealpeopleLd = new DLineEdit;

    m_OkBtn = new DPageBtn(this,"OK");
    m_CancelBtn = new DPageBtn(this,"Cancel");
    m_OkBtn->setFixedSize(300, 200);
    m_CancelBtn->setFixedSize(300, 200);
    QHBoxLayout* NumHbox = new QHBoxLayout;
    NumHbox->addWidget(m_BookNum);
    NumHbox->addWidget(m_BookNumLd);
    NumHbox->setSpacing(30);
    QHBoxLayout* NameHbox = new QHBoxLayout;
    NameHbox->addWidget(m_BookName);
    NameHbox->addWidget(m_BookNameLd);
    NameHbox->setSpacing(30);
    QHBoxLayout* AuthorHbox = new QHBoxLayout;
    AuthorHbox->addWidget(m_Author);
    AuthorHbox->addWidget(m_AuthorLd);
    AuthorHbox->setSpacing(30);
    QHBoxLayout* CategoryHbox = new QHBoxLayout;
    CategoryHbox->addWidget(m_Category);
    CategoryHbox->addWidget(m_CategoryLd);
    CategoryHbox->setSpacing(30);
    QHBoxLayout* PublisherHbox = new QHBoxLayout;
    PublisherHbox->addWidget(m_Publisher);
    PublisherHbox->addWidget(m_PublisherLd);
    PublisherHbox->setSpacing(30);
    QHBoxLayout* TotalinventoryHbox = new QHBoxLayout;
    TotalinventoryHbox->addWidget(m_Totalinventory);
    TotalinventoryHbox->addWidget(m_TotalinventoryLd);
    TotalinventoryHbox->setSpacing(30);
    QHBoxLayout* TotalavailableHbox = new QHBoxLayout;
    TotalavailableHbox->addWidget(m_Totalavailable);
    TotalavailableHbox->addWidget(m_TotalavailableLd);
    TotalavailableHbox->setSpacing(30);
    QHBoxLayout* DealpeopleHbox = new QHBoxLayout;
    DealpeopleHbox->addWidget(m_Dealpeople);
    DealpeopleHbox->addWidget(m_DealpeopleLd);
    DealpeopleHbox->setSpacing(30);

    QHBoxLayout* btnHbox = new QHBoxLayout;
    btnHbox->addWidget(m_CancelBtn);
    btnHbox->addWidget(m_OkBtn);

    QHBoxLayout* lineHbox1 = new QHBoxLayout;
    lineHbox1->addLayout(NumHbox);
    lineHbox1->addLayout(NameHbox);
    QHBoxLayout* lineHbox2 = new QHBoxLayout;
    lineHbox2->addLayout(AuthorHbox);
    lineHbox2->addLayout(CategoryHbox);
    QHBoxLayout* lineHbox3 = new QHBoxLayout;
    lineHbox3->addLayout(PublisherHbox);
    lineHbox3->addLayout(TotalinventoryHbox);
    QHBoxLayout* lineHbox4 = new QHBoxLayout;
    lineHbox4->addLayout(TotalavailableHbox);
    lineHbox4->addLayout(DealpeopleHbox);

    QVBoxLayout* layVbox = new QVBoxLayout;
    layVbox->addLayout(lineHbox1);
    layVbox->addLayout(lineHbox2);
    layVbox->addLayout(lineHbox3);
    layVbox->addLayout(lineHbox4);
    layVbox->addLayout(btnHbox);

    setLayout(layVbox);

    connect(m_OkBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnOkBtnClienk()));

    //booknum     bookname    author      category    publisher   totalinventory  totalavailable  dealpeople  entrytime
    m_BookNumLd->setText("20000006");
    m_BookNameLd->setText("巴黎圣母院");
    m_AuthorLd->setText("维克多·雨果");
    m_CategoryLd->setText("文学");
    m_PublisherLd->setText("人民出版社");
    m_TotalinventoryLd->setText("4");
    m_TotalavailableLd->setText("4");
    m_DealpeopleLd->setText("小唐");
}

void BookManagement::BookManageMsg(SocketMsg msg)
{
    DDialog *Dialog = new DDialog(360, 200, this);
    Dialog->setTitleName("Rename");  //Rename
    DialogWidget *dig = new DialogWidget(Dialog);
    //dig->SetShowLb("hello world!", "rgb(255,128,0)");
    dig->SetShowLb(msg.firstmsg, "red");
    Dialog->setContentWidget(dig);
    connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
    Dialog->exec();
}

void BookManagement::OnOkBtnClienk()
{
    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    if (Socket != NULL)
    {
        QString sendmsg = QString("{ \n"
            "\"status\":\"9\",  \n"
            "\"firstmsg\" : \"%1-%2\",\n"
            "\"secondmsg\" : \"%3-%4\", \n"
            "\"thirdmsg\" : \"%5-%6\", \n"
            "\"fourthmsg\" :\"%7-%8\" };").arg(m_BookNumLd->text()).arg(m_BookNameLd->text())
                                  .arg(m_AuthorLd->text()).arg(m_CategoryLd->text())
                                  .arg(m_PublisherLd->text()).arg(m_TotalinventoryLd->text())
                                  .arg(m_TotalavailableLd->text()).arg(m_DealpeopleLd->text());
        Socket->write(sendmsg.toUtf8());
    }
}