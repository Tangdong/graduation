#include "BorrowInterface.h"
#include "GraduationDesign.h"

BorrowInterface::BorrowInterface(QWidget *parent)
    : QWidget(parent)
{
    InitGui();
    m_count = 0;
    m_bookcount = 0;
    m_bcont = true;
    m_bSearch = true;
}

BorrowInterface::~BorrowInterface()
{
}

void BorrowInterface::InitGui()
{
    m_NameLb = new QLabel("读者：");
    m_IDLb = new QLabel("账号：");
    m_NameShowLb = new DLabel(this);
    m_IDShowLb = new DLabel(this);
    m_SearchBtn = new DPageBtn(this);
    m_SearchLed = new DLineEdit(this);
    m_tablewidget = new DTableWidget;


    m_MenuBtn = new DPageBtn(this, "查询类别");
    m_MenuBtn->SetId(-1);
    m_Menu = new QMenu;

    m_MenuBtn->setFixedSize(80, 30);
    m_Menu->setStyleSheet(qssMenu);
    QAction *booknumAct = new QAction("书籍编号", m_MenuBtn);//Rename
    m_Menu->addAction(booknumAct);
    QAction *booknameAct = new QAction("书籍名称", m_MenuBtn);//Rename
    m_Menu->addAction(booknameAct);
    QAction *catagoryAct = new QAction("书籍类别", m_MenuBtn);//Refresh
    m_Menu->addAction(catagoryAct);
    QAction *authorAct = new QAction("作者名", m_MenuBtn);//Remove
    //author->setIcon(QPixmap(":/res/menu/icon/icon_list_delete_normal.png"));
    m_Menu->addAction(authorAct);
    connect(booknumAct, &QAction::triggered, this, &BorrowInterface::OnSearchBooknumAct);
    connect(booknameAct, &QAction::triggered, this, &BorrowInterface::OnSearchBooknaemAct);
    connect(catagoryAct, &QAction::triggered, this, &BorrowInterface::OnSearchCatagoryAct);
    connect(authorAct, &QAction::triggered, this, &BorrowInterface::OnSearchAuthorAct);


    m_BottomLb = new QLabel("您还可以借阅2本书");
    m_BorrowBtn = new DPageBtn(this, "借阅", BUTTON_TEXT);
    m_BorrowBtn->SetEnable(true);

    QHBoxLayout* NameHbox = new QHBoxLayout;
    NameHbox->addWidget(m_NameLb);
    NameHbox->addWidget(m_NameShowLb);
    QHBoxLayout* IDHbox = new QHBoxLayout;
    IDHbox->addWidget(m_IDLb);
    IDHbox->addWidget(m_IDShowLb);
    QHBoxLayout* SearchHbox = new QHBoxLayout;
    SearchHbox->addWidget(m_MenuBtn);
    SearchHbox->addWidget(m_SearchLed);
    SearchHbox->addWidget(m_SearchBtn);

    QHBoxLayout* layHbox = new QHBoxLayout;
    layHbox->addLayout(NameHbox);
    layHbox->addStretch();
    layHbox->addLayout(IDHbox);
    layHbox->addStretch();
    layHbox->addLayout(SearchHbox);

    QHBoxLayout* bottomhbox = new QHBoxLayout;
    bottomhbox->addWidget(m_BottomLb);
    bottomhbox->addStretch();
    bottomhbox->addWidget(m_BorrowBtn);
    bottomhbox->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* layVbox = new QVBoxLayout;
    layVbox->addLayout(layHbox);
    layVbox->addWidget(m_tablewidget);
    layVbox->addSpacing(10);
    layVbox->addLayout(bottomhbox);
    setLayout(layVbox);

    QTableWidgetItem* headerItem;
    QStringList headerText;

    //表头标题用QStringList来表示
    headerText << "选择" << "书籍编号" << "书名" << "作者" << "类别" << "出版社" << "库存总量" << "现存总量" << "入馆时间";
    m_tablewidget->setColumnCount(headerText.count());//列数设置为与 headerText的行数相等
    m_tablewidget->setColumnWidth(0, 60);
    for (int i = 0; i < m_tablewidget->columnCount(); i++)//列编号从0开始
    {
        //cellItem=ui->tableInfo->horizontalHeaderItem(i);
        headerItem = new QTableWidgetItem(headerText.at(i)); //新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
        QFont font = headerItem->font();//获取原有字体设置
        //font.setBold(true);//设置为粗体
        font.setPointSize(12);//字体大小
        //headerItem->setTextColor(Qt::red);//字体颜色
        headerItem->setFont(font);//设置字体
        m_tablewidget->setHorizontalHeaderItem(i, headerItem); //设置表头单元格的Item
    }
    headerText.clear();
    connect(m_tablewidget, SIGNAL(cellChanged(int, int)), this, SLOT(CheckBoxChange(int, int)));
    connect(m_BorrowBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnBorrowBtnClick()));
    connect(m_SearchBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnSearchBtnClick()));
    connect(m_tablewidget, SIGNAL(OnScrollBarArriveBottom()), this, SLOT(OnScrollBarArriveBottom()));
    connect(m_MenuBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnMenuBtnClick()));
}

void BorrowInterface::OnScrollBarArriveBottom()
{
    int num = m_tablewidget->rowCount();
    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    if (Socket != NULL)
    {
        QString sendmsg = QString("{ \n"
            "\"status\":\"10\",  \n"
            "\"firstmsg\" : \"%1 limit %2,%3\",\n"
            "\"secondmsg\" : \"2\", \n"
            "\"thirdmsg\" : \"3\", \n"
            "\"fourthmsg\" :\"4\" };").arg(m_sqlwhere).arg(num).arg(2);
        Socket->write(sendmsg.toUtf8());
    }
}

void BorrowInterface::OnSearchBtnClick()
{
    if (!m_bSearch)
    {
        //return;
    }
    m_bSearch = false;
    m_tablewidget->ClearTable();
    QString sqlstr = m_SearchLed->text();
    QString sqlwhere;
    if (!sqlstr.isEmpty())
    {
        switch (m_MenuBtn->GetId())
        {
        case BOOKNUM:
            sqlwhere = "booknum";
            break;
        case BOOKNAME:
            sqlwhere = "bookname";
            break;
        case CATAGORY:
            sqlwhere = "category";
            break;
        case AUTHOR:
            sqlwhere = "author";
            break;
        case PUBLISHER:
            sqlwhere = "publisher";
            break;
        default:
            sqlwhere.clear();
            break;
        }
        if (sqlwhere.isEmpty())
        {
            m_sqlwhere = "";
        }
        else
        {
            m_sqlwhere = QString("where %1 like '%%2%'").arg(sqlwhere).arg(sqlstr);
        }
    }
    else
    {
        m_sqlwhere = "";
    }
    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    if (Socket != NULL)
    {
        QString sendmsg = QString("{ \n"
            "\"status\":\"10\",  \n"
            "\"firstmsg\" : \"%1 limit 0,5\",\n"
            "\"secondmsg\" : \"2\", \n"
            "\"thirdmsg\" : \"3\", \n"
            "\"fourthmsg\" :\"4\" };").arg(m_sqlwhere);
        Socket->write(sendmsg.toUtf8());
    }
}

void BorrowInterface::OnBorrowBtnClick()
{
    //借阅次数不足
    if (g_userinfo->borrownum <= 0)
    {
        DDialog *Dialog = new DDialog(360, 200, this);
        Dialog->setTitleName("Borrow Error");  //Rename
        DialogWidget *dig = new DialogWidget(Dialog);
        //dig->SetShowLb("hello world!", "rgb(255,128,0)");
        dig->SetShowLb("您的借阅次数不足，如果想重新借阅请先归还书籍！", "red");
        Dialog->setContentWidget(dig);
        connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
        Dialog->exec();
        ClearCheckItem();
        return;
    }
    m_bcont = false;
    for (int i = 0; i < m_tablewidget->rowCount(); i++)
    {
        if (m_tablewidget->item(i, 0)->checkState() == Qt::Checked)
        {
            m_bookcount++;
            m_CheckBookVector.push_back(m_tablewidget->GetIndexText(i, 1));
        }
    }
    m_bcont = true;

    GraduationDesign* Grd = (GraduationDesign*)g_Graduation;
    ReturnInterface* ReturnBook = Grd->GetReturnInterface();
    std::vector<Bookinfo> bookinfoVector = Grd->GetSaveBookVector();
    std::vector<QString>::iterator it = m_CheckBookVector.begin();
    for (int i = 0; i < bookinfoVector.size(); i++)
    {
        it = m_CheckBookVector.begin();
        for (; it < m_CheckBookVector.end();it++)
        {
            if (bookinfoVector[i].booknum == *it)
            {
                //查找到有这本书后，判断是否归过，如果归还依旧可以借阅
                if (ReturnBook->IsReturn(bookinfoVector[i].booknum))
                {
                    continue;
                }
                BorrowRepeat(bookinfoVector[i].bookname);
                m_CheckBookVector.erase(it);
                m_bookcount--;
                ChangeCheckBoxState(bookinfoVector[i].booknum);
                break;
            }
        }
    }
    if ( 0 == m_CheckBookVector.size())
    {
        return;
    }
    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    if (Socket != NULL)
    {
        for (int i = 0; i < m_CheckBookVector.size(); i++)
        {
            QString sendmsg = QString("{ \n"
                "\"status\":\"2\",  \n"
                "\"firstmsg\" : \"%1\",\n"
                "\"secondmsg\" : \"%2\", \n"
                "\"thirdmsg\" : \"3\", \n"
                "\"fourthmsg\" :\"4\" };").arg(g_userinfo->usernum).arg(m_CheckBookVector[i]);
            Socket->write(sendmsg.toUtf8());
        }
    }
}

void BorrowInterface::CheckBoxChange(int row, int column)
{
    if ( !m_bcont )
    {
        return;
    }
    if (m_tablewidget->item(row, column)->checkState() == Qt::Checked )
    {
        m_count++;
    }
    else
    {
        m_count--;
    }
    ChangeBtnState(m_count);
}
void BorrowInterface::ChangeBtnState(int m_count)
{
    qDebug() << "m_count = " << m_count;
    if ( m_count == 0)
    {
        m_BorrowBtn->SetEnable(true);
    }
    else
    {
        m_BorrowBtn->SetEnable(false);
    }
}

void BorrowInterface::BorrowResult(SocketMsg msg, bool b)
{
    int row = ChangeCheckBoxState(msg.secondmsg);
    //不管是否失败改变checkbox选中状态
    if (!b)
    {
        //借阅失败
        DDialog *Dialog = new DDialog(360, 200, this);
        Dialog->setTitleName("Borrow Result");  //Rename
        DialogWidget *dig = new DialogWidget(Dialog);
        //dig->SetShowLb("hello world!", "rgb(255,128,0)");
        dig->SetShowLb("借阅失败！" + msg.secondmsg, "red");
        Dialog->setContentWidget(dig);
        connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
        Dialog->exec();
        //删除本地保留的vector
        std::vector<QString>::iterator it = m_CheckBookVector.begin();
        it = m_CheckBookVector.begin();
        for (; it < m_CheckBookVector.end(); it++)
        {
            if (*it == msg.secondmsg)
            {
                m_bookcount--;
                m_CheckBookVector.erase(it);
                break;
            }
        }
    }
    //借阅成功
    //1.更新每个页面的可借阅书籍的数目
    g_userinfo->borrownum = g_userinfo->borrownum - 1;
    emit SigUserInfoUpdate();

    //2.修改借阅书籍表,添加归还书籍表,添加借阅信息表
    QString nowBook = m_tablewidget->GetIndexText(row, 7);
    m_tablewidget->item(row, 7)->setText(QString("%1").arg(nowBook.toInt() - 1));
    m_bookcount--;
    if (m_bookcount != 0)
    {
        return;
    }
    if (m_CheckBookVector.size() == 0)
    {
        return;
    }
    QString text;
    Bookinfo book;
    GraduationDesign* Grd = (GraduationDesign*)g_Graduation;
    for (int i = 0; i < m_CheckBookVector.size(); i++)
    {
        book = Grd->GetSaveBook(m_CheckBookVector[i]);
        text += book.bookname + ",";
    }
    text = text.left(text.length() - 1);
    DDialog *Dialog = new DDialog(360, 200, this);
    Dialog->setTitleName("Borrow Result");  //Rename
    DialogWidget *dig = new DialogWidget(Dialog);
    //dig->SetShowLb("hello world!", "rgb(255,128,0)");
    dig->SetShowLb("您已经成功借阅 :" + text + "!", "red");
    Dialog->setContentWidget(dig);
    connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
    Dialog->exec();
    m_CheckBookVector.clear();
    m_count = 0;
    ChangeBtnState(m_count);
}


void BorrowInterface::BorrowMsg(SocketMsg msg)
{
    if (msg.firstmsg == "BORROW_OK")
    {
        qDebug() << "借阅成功";
        BorrowResult(msg,true);
        return;
    }
    if (msg.firstmsg == "BORROW_ERROR")
    {
        qDebug() << "借阅失败";
        BorrowResult(msg, false);
        return;
    }

    QStringList listmsg;

    QStringList list = msg.firstmsg.split("-");
    listmsg << list[0] << list[1];

    list.clear();
    list = msg.secondmsg.split("-");
    listmsg << list[0] << list[1] << list[2];
    
    list.clear();
    list = msg.thirdmsg.split("-");
    listmsg << list[0] << list[1];

    list.clear();
    list = msg.fourthmsg.split("-");
    unsigned long booktime = list[1].toULong();
    QDateTime dataTime = QDateTime::fromTime_t(booktime);
    QString startTime;
    startTime = dataTime.toString("yyyy-MM-dd");

    listmsg << startTime;

    m_bcont = false;
    m_tablewidget->MySetItem(listmsg);
    m_bcont = true;
    m_bSearch = true;
}

void BorrowInterface::ViewDetail(QTableWidgetItem* item)
{
    qDebug() << tr("查看详情");
    qDebug() << item->text();
    qDebug() << item->row();
    qDebug() << item->column();
    //item->setTextColor(QColor(255, 215, 0));
    //item->setText("love");
}



void BorrowInterface::BorrowRepeat(QString text)
{
    //delete m_Socket;
    DDialog *Dialog = new DDialog(360, 200, this);
    Dialog->setTitleName("Borrow Error");  //Rename
    DialogWidget *dig = new DialogWidget(Dialog);
    //dig->SetShowLb("hello world!", "rgb(255,128,0)");
    dig->SetShowLb("你已经借阅了"+ text +",不能重复借阅！", "red");
    Dialog->setContentWidget(dig);
    connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
    Dialog->exec();
}



int BorrowInterface::ChangeCheckBoxState(QString booknum)
{
    int row = m_tablewidget->rowCount();
    for (int i = 0; i < row; i++)
    {
        //m_tablewidget->item(i, 0)->checkState();
        if (m_tablewidget->GetIndexText(i,1) == booknum)
        {
            m_bcont = false;
            m_tablewidget->item(i, 0)->setCheckState(Qt::Unchecked);
            m_bcont = true;
            m_count--;
            ChangeBtnState(m_count);
            return i;
        }
    }
    return -1;
}

void BorrowInterface::UpdateUserInfo()
{
    if (g_userinfo == NULL)
    {
        return;
    }

    m_NameLb->setText("读者：" + g_userinfo->username);
    m_IDLb->setText("账号：" + g_userinfo->usernum);
    m_BottomLb->setText(QString("您还可以借阅 %1 本书").arg(g_userinfo->borrownum));
}

void BorrowInterface::ClearCheckItem()
{
    int row = m_tablewidget->rowCount();
    for (int i = 0; i < row; i++)
    {
        m_tablewidget->item(i, 0)->setCheckState(Qt::Unchecked);
    }
    m_count = 0;
}


void BorrowInterface::OnMenuBtnClick()
{
    QPoint pos;
    QRect rect;
    rect = m_MenuBtn->geometry();
    pos.setX(rect.x());
    pos.setY(rect.y() + rect.height());
    m_Menu->exec(this->mapToGlobal(pos));
}


void BorrowInterface::OnSearchBooknaemAct()
{
    m_MenuBtn->SetText("书籍名称");
    m_MenuBtn->SetId(BOOKNAME);
}

void BorrowInterface::OnSearchBooknumAct()
{
    m_MenuBtn->SetText("书籍编号");
    m_MenuBtn->SetId(BOOKNUM);
}

void BorrowInterface::OnSearchCatagoryAct()
{
    m_MenuBtn->SetText("书籍类别");
    m_MenuBtn->SetId(CATAGORY);
}

void BorrowInterface::OnSearchAuthorAct()
{
    m_MenuBtn->SetText("书籍作者");
    m_MenuBtn->SetId(AUTHOR);
}