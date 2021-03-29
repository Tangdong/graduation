#include "ReturnInterface.h"
#include "GraduationDesign.h"

ReturnInterface::ReturnInterface(QWidget *parent)
    : QWidget(parent)
{
    InitGui();
    m_count = 0;
    m_itemCount = 0;
    m_bcont = true;

}

ReturnInterface::~ReturnInterface()
{
}

void ReturnInterface::InitGui()
{
    m_NameLb = new QLabel("���ߣ�");
    m_IDLb = new QLabel("�˺ţ�");
    m_NameShowLb = new DLabel(this);
    m_IDShowLb = new DLabel(this);
    m_SearchBtn = new DPageBtn(this);
    m_SearchLed = new DLineEdit(this);
    m_tablewidget = new DTableWidget;
    m_MenuBtn = new DPageBtn(this,"�鼮���");
    m_Menu = new QMenu;

    m_MenuBtn->setFixedSize(80, 30);
    m_Menu->setStyleSheet(qssMenu);
    QAction *booknumAct = new QAction("�鼮���", m_MenuBtn);//Rename
    m_Menu->addAction(booknumAct);
    QAction *booknameAct = new QAction("�鼮����", m_MenuBtn);//Rename
    m_Menu->addAction(booknameAct);
    QAction *catagoryAct = new QAction("�鼮���", m_MenuBtn);//Refresh
    m_Menu->addAction(catagoryAct);
    QAction *authorAct = new QAction("������", m_MenuBtn);//Remove
    //author->setIcon(QPixmap(":/res/menu/icon/icon_list_delete_normal.png"));
    m_Menu->addAction(authorAct);
    connect(booknumAct,  &QAction::triggered, this, &ReturnInterface::OnSearchBooknumAct);
    connect(booknameAct, &QAction::triggered, this, &ReturnInterface::OnSearchBooknaemAct);
    connect(catagoryAct, &QAction::triggered, this, &ReturnInterface::OnSearchCatagoryAct);
    connect(authorAct,   &QAction::triggered, this, &ReturnInterface::OnSearchAuthorAct);

    m_BottomLb = new QLabel("�������Խ���2����");
    m_ReturnBtn = new DPageBtn(this, "�黹", BUTTON_TEXT);
    m_ReturnBtn->SetEnable(true);

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
    bottomhbox->addWidget(m_ReturnBtn);
    bottomhbox->setContentsMargins(0, 0, 0, 0);


    QVBoxLayout* layVbox = new QVBoxLayout;
    layVbox->addLayout(layHbox);
    layVbox->addWidget(m_tablewidget);
    layVbox->addSpacing(10);
    layVbox->addLayout(bottomhbox);

    setLayout(layVbox);

    QTableWidgetItem* headerItem;
    QStringList headerText;

    //��ͷ������QStringList����ʾ
    headerText << "ѡ��" << "���ı��" << "�鼮���" <<"����" << "���߱��" << "��������" << "����ʱ��" << "����ʱ��" << "���������";
    m_tablewidget->setColumnCount(headerText.count());//��������Ϊ�� headerText���������
    m_tablewidget->setColumnWidth(0, 60);
    for (int i = 0; i < m_tablewidget->columnCount(); i++)//�б�Ŵ�0��ʼ
    {
        //cellItem=ui->tableInfo->horizontalHeaderItem(i);
        headerItem = new QTableWidgetItem(headerText.at(i)); //�½�һ��QTableWidgetItem�� headerText.at(i)��ȡheaderText��i���ַ���
        QFont font = headerItem->font();//��ȡԭ����������
        //font.setBold(true);//����Ϊ����
        font.setPointSize(12);//�����С
        //headerItem->setTextColor(Qt::red);//������ɫ
        headerItem->setFont(font);//��������
        m_tablewidget->setHorizontalHeaderItem(i, headerItem); //���ñ�ͷ��Ԫ���Item
    }
    connect(m_tablewidget, SIGNAL(cellChanged(int, int)), this, SLOT(CheckBoxChange(int, int)));
    connect(m_ReturnBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnReturnBtnClick()));
    connect(m_SearchBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnSearchBtnClick()));
    connect(m_MenuBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnMenuBtnClick()));
}

void ReturnInterface::CheckBoxChange(int row, int column)
{
    if (!m_bcont)
    {
        return;
    }
    if (m_tablewidget->item(row, column)->checkState() == Qt::Checked)
    {
        m_count++;
    }
    else
    {
        m_count--;
    }
    ChangeBtnState(m_count);
}
void ReturnInterface::ChangeBtnState(int m_count)
{
    qDebug() << "m_count = " << m_count;
    if (m_count == 0)
    {
        m_ReturnBtn->SetEnable(true);
    }
    else
    {
        m_ReturnBtn->SetEnable(false);
    }
}

void ReturnInterface::ReturnResult(SocketMsg msg, bool b)
{
    g_userinfo->borrownum += 1;
    unsigned long t = msg.fourthmsg.toULong();
    SetReturnTime(msg.thirdmsg, t);

    m_itemCount--;
    if (m_itemCount != 0)
    {
        return;
    }
    QString text;
    for (int i = 0; i < m_CheckBookVector.size();i++)
    {
        Bookinfo book = GetBookinfoItem(m_CheckBookVector[i]);
        text += book.bookname + ",";
    }
    text = text.left(text.length() - 1);

    DDialog *Dialog = new DDialog(360, 200, this);
    Dialog->setTitleName("Borrow Result");  //Rename
    DialogWidget *dig = new DialogWidget(Dialog);
    dig->SetShowLb("���Ѿ��ɹ��黹��" + text + "!", "red");
    Dialog->setContentWidget(dig);
    connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
    Dialog->exec();

    m_CheckBookVector.clear();
    SetTableData();
    m_count = 0;
    ChangeBtnState(m_count);
    emit SigUserInfoUpdate();
}

void ReturnInterface::ReturnMsg(SocketMsg msg)
{
    if (msg.firstmsg == "RETURN_OK")
    {
        qDebug() << "�黹�ɹ�";
        ReturnResult(msg,true);
        return;
    }
    if (msg.firstmsg == "RETURN_ERROR")
    {
        qDebug() << "�黹ʧ��";
        DDialog *Dialog = new DDialog(360, 200, this);
        Dialog->setTitleName("Borrow Result");  //Rename
        DialogWidget *dig = new DialogWidget(Dialog);
        //dig->SetShowLb("hello world!", "rgb(255,128,0)");
        dig->SetShowLb("�黹ʧ�ܣ�" + msg.secondmsg, "red");
        Dialog->setContentWidget(dig);
        connect(Dialog, SIGNAL(sigCloseDlg()), dig, SLOT(onCloseDlg()));
        Dialog->exec();
        return;
    }

    Borrowinfo borrow;
    QStringList list = msg.firstmsg.split("-");
    borrow.borrownum = list[0];
    borrow.booknum = list[1];


    list.clear();
    list = msg.secondmsg.split("-");
    borrow.usernum = list[0];
    //borrow.borrownum = list[1];

    list.clear();
    list = msg.thirdmsg.split("-");
    borrow.borrowtime = list[0].toULong();
    borrow.nowtime = list[1].toULong();

    list.clear();
    list = msg.fourthmsg.split("-");
    borrow.renewalnum = list[0].toInt();
    borrow.returntime = list[1].toULong();

    m_borrowVector.push_back(borrow);
    //m_bcont = false;
    //m_tablewidget->MySetItem(listmsg);
    //m_bcont = true;
}

void ReturnInterface::ViewDetail(QTableWidgetItem* item)
{

}

void ReturnInterface::OnReturnBtnClick()
{

    for (int i = 0; i < m_tablewidget->rowCount(); i++)
    {
        if (m_tablewidget->item(i, 0)->checkState() == Qt::Checked)
        {
            m_itemCount++;
            m_CheckBookVector.push_back(m_tablewidget->GetIndexText(i, 1));
        }
    }

    //�Ƿ�Ƿ�ѣ�Ƿ�Ѳ��ܹ黹
    //if (1)
    //{
    //}

    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    if (Socket == NULL)
    {
        qDebug() << "�������ӳ���";
        return;
    }
    for (int i = 0; i < m_CheckBookVector.size();i++)
    {
        Borrowinfo borrow;
        borrow = GetBorrowinfoItem(m_CheckBookVector[i]);
        QString sendmsg = QString("{ \n"
            "\"status\":\"3\",  \n"
            "\"firstmsg\" : \"%1\",\n"
            "\"secondmsg\" : \"%2\", \n"
            "\"thirdmsg\" : \"%3\", \n"
            "\"fourthmsg\" :\"4\" };").arg(g_userinfo->usernum).arg(borrow.booknum).arg(borrow.borrownum);
        Socket->write(sendmsg.toUtf8());
    }

}

Bookinfo ReturnInterface::GetBookinfoItem(QString borrownum)
{
    Borrowinfo borrow = GetBorrowinfoItem(borrownum);
    GraduationDesign *Grd = (GraduationDesign*)g_Graduation;
    Bookinfo book = Grd->GetSaveBook(borrow.booknum);
    return book;
}

Borrowinfo ReturnInterface::GetBorrowinfoItem(QString borrownum)
{
    Borrowinfo borrow;
    for (int i = 0; i < m_borrowVector.size();i++)
    {
        if (m_borrowVector[i].borrownum == borrownum)
        {
            borrow = m_borrowVector[i];
            break;
        }
    }
    return borrow;
}

void ReturnInterface::UpdateUserInfo()
{
    if (g_userinfo == NULL)
    {
        return;
    }

    m_NameLb->setText("���ߣ�" + g_userinfo->username);
    m_IDLb->setText("�˺ţ�" + g_userinfo->usernum);
    m_BottomLb->setText(QString("�������Խ��� %1 ����").arg(g_userinfo->borrownum));
}

void ReturnInterface::SetReturnTime(QString borrownum,unsigned long returntime)
{
    for (int i = 0; i < m_borrowVector.size();i++)
    {
        if (m_borrowVector[i].borrownum == borrownum)
        {
            m_borrowVector[i].returntime = returntime;
            m_borrowVector[i].nowtime = returntime;
            break;
        }
    }
    SetTableData();
}

void ReturnInterface::DeleteBorrowVectorItem(QString borrownum)
{
    GraduationDesign* Grd = (GraduationDesign*)g_Graduation;
    std::vector<Borrowinfo>::iterator it =  m_borrowVector.begin();
    for (; it != m_borrowVector.end(); it++)
    {
        if (it->borrownum == borrownum)
        {
            //ɾ����¼����Ҫͬʱɾ�����ر����Ľ�����Ϣ
            Grd->DeleteBookinfoItem(it->booknum);
            m_borrowVector.erase(it);
            break;
        }
    }
}

bool ReturnInterface::IsReturn(QString booknum)
{
    bool result = false;
    for (int i = 0; i < m_borrowVector.size(); i++)
    {
        if (m_borrowVector[i].booknum == booknum)
        {
            if (m_borrowVector[i].returntime > m_borrowVector[i].borrowtime)
            {
                result = true;
                return result;
            }
        }
    }
    return result;
}

void ReturnInterface::SetTableData()
{
    m_bcont = false;
    m_tablewidget->ClearTable();
    QStringList list;
    GraduationDesign *Grd = (GraduationDesign*)g_Graduation;
    for (int i = 0; i < m_borrowVector.size(); i++)
    {
        if (m_borrowVector[i].returntime > m_borrowVector[i].borrowtime)
        {
            continue;
        }
        list.clear();
        Bookinfo book = Grd->GetSaveBook(m_borrowVector[i].booknum);
        QDateTime borrowTime = QDateTime::fromTime_t(m_borrowVector[i].borrowtime);
        QString str_borrowTime = borrowTime.toString("yyyy-MM-dd");
        QDateTime outTime = QDateTime::fromTime_t(m_borrowVector[i].borrowtime + 30 * 24 * 60 * 60 * (3 - m_borrowVector[i].renewalnum));
        QString str_outTime = outTime.toString("yyyy-MM-dd");
        list << m_borrowVector[i].borrownum << book.booknum << book.bookname << g_userinfo->usernum << g_userinfo->username << 
            str_borrowTime << str_outTime << QString("%1").arg(m_borrowVector[i].renewalnum);
        m_tablewidget->MySetItem(list);
    }
    m_bcont = true;
    m_count = 0;
}

std::vector<Borrowinfo> ReturnInterface::GetBorrowinfoData()
{
    return m_borrowVector;
}

void ReturnInterface::OnMenuBtnClick()
{
    QPoint pos;
    QRect rect;
    rect = m_MenuBtn->geometry();
    //pos = this->mapToGlobal(m_MenuBtn->pos());
    //int x = pos.x();
    //int y = pos.y();
    pos.setX(rect.x());
    pos.setY(rect.y() + rect.height());
    m_Menu->exec(this->mapToGlobal(pos));
}

void ReturnInterface::OnSearchBooknaemAct()
{
    m_MenuBtn->SetText("�鼮����");
    m_MenuBtn->SetId(BOOKNAME);
}

void ReturnInterface::OnSearchBooknumAct()
{
    m_MenuBtn->SetText("�鼮���");
    m_MenuBtn->SetId(BOOKNUM);
}

void ReturnInterface::OnSearchCatagoryAct()
{
    m_MenuBtn->SetText("�鼮���");
    m_MenuBtn->SetId(CATAGORY);

}

void ReturnInterface::OnSearchAuthorAct()
{
    m_MenuBtn->SetText("�鼮����");
    m_MenuBtn->SetId(AUTHOR);
}

void ReturnInterface::OnSearchBtnClick()
{
    m_bcont = false;
    m_tablewidget->ClearTable();
    int statu = m_MenuBtn->GetId();
    QStringList list;
    QString searchStr = m_SearchLed->text();
    GraduationDesign *Grd = (GraduationDesign*)g_Graduation;
    for (int i = 0; i < m_borrowVector.size(); i++)
    {
        if (m_borrowVector[i].returntime > m_borrowVector[i].borrowtime)
        {
            continue;
        }
        Bookinfo book = Grd->GetSaveBook(m_borrowVector[i].booknum);
        if (!DLFUNC::SearchItem(book,searchStr,statu))
        {
            continue;
        }
        list.clear();
        QDateTime borrowTime = QDateTime::fromTime_t(m_borrowVector[i].borrowtime);
        QString str_borrowTime = borrowTime.toString("yyyy-MM-dd");
        QDateTime outTime = QDateTime::fromTime_t(m_borrowVector[i].borrowtime + 30 * 24 * 60 * 60 * (3 - m_borrowVector[i].renewalnum));
        QString str_outTime = outTime.toString("yyyy-MM-dd");
        list << m_borrowVector[i].borrownum << book.booknum << book.bookname << g_userinfo->usernum << g_userinfo->username <<
            str_borrowTime << str_outTime << QString("%1").arg(m_borrowVector[i].renewalnum);
        m_tablewidget->MySetItem(list);
    }
    m_bcont = true;
    m_count = 0;
}