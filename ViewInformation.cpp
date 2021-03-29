#include "ViewInformation.h"
#include "GraduationDesign.h"

ViewInformation::ViewInformation(QWidget *parent)
    : QWidget(parent)
{
    InitGui();
    m_count = 0;
    m_bcont = true;
}

ViewInformation::~ViewInformation()
{
}

void ViewInformation::InitGui()
{
    m_NameLb = new QLabel("���ߣ�");
    m_IDLb = new QLabel("�˺ţ�");
    m_NameShowLb = new DLabel(this);
    m_IDShowLb = new DLabel(this);
    m_SearchBtn = new DPageBtn(this);
    m_SearchLed = new DLineEdit(this);
    m_tablewidget = new DTableWidget;


    m_MenuBtn = new DPageBtn(this, "�鼮���");
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
    connect(booknumAct,  &QAction::triggered, this, &ViewInformation::OnSearchBooknumAct);
    connect(booknameAct, &QAction::triggered, this, &ViewInformation::OnSearchBooknaemAct);
    connect(catagoryAct, &QAction::triggered, this, &ViewInformation::OnSearchCatagoryAct);
    connect(authorAct,   &QAction::triggered, this, &ViewInformation::OnSearchAuthorAct);

    m_BottomLb = new QLabel("�������Խ���2����");
    m_DeleteBtn = new DPageBtn(this, "ɾ��", BUTTON_TEXT);
    m_DeleteBtn->SetEnable(true);

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
    bottomhbox->addWidget(m_DeleteBtn);
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
    headerText << "ѡ��" << "���ı��" <<"�鼮���" << "����" << "���߱��" << "������" << "״̬" << "�黹ʱ��" <<"����";
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
    headerText.clear();
    connect(m_tablewidget, SIGNAL(cellChanged(int, int)), this, SLOT(CheckBoxChange(int, int)));
    connect(m_DeleteBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnDeleteBtnClick()));
    connect(m_SearchBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnSearchBtnClick()));
    connect(m_MenuBtn, SIGNAL(PageBtnClienk()), this, SLOT(OnMenuBtnClick()));
}

void ViewInformation::CheckBoxChange(int row, int column)
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

void ViewInformation::ChangeBtnState(int m_count)
{
    qDebug() << "m_count = " << m_count;
    if (m_count == 0)
    {
        m_DeleteBtn->SetEnable(true);
    }
    else
    {
        m_DeleteBtn->SetEnable(false);
    }
}

void ViewInformation::ViewInfoMsg(SocketMsg msg)
{
    if (msg.firstmsg == "DELETE_ERROR")
    {
        qDebug() << "ɾ��ʧ��";
        return;
    }
    if (msg.firstmsg == "DELETE_OK")
    {
        qDebug() << "ɾ���ɹ�";
        GraduationDesign* Grd = (GraduationDesign*)g_Graduation;
        ReturnInterface *ret = Grd->GetReturnInterface();
        ret->DeleteBorrowVectorItem(msg.secondmsg);
        SetTableData();
    }
}

void ViewInformation::ViewDetail(QTableWidgetItem* item)
{

}

void ViewInformation::UpdateUserInfo()
{
    if (g_userinfo == NULL)
    {
        return;
    }

    m_NameLb->setText("���ߣ�" + g_userinfo->username);
    m_IDLb->setText("�˺ţ�" + g_userinfo->usernum);
    m_BottomLb->setText(QString("�������Խ��� %1 ����").arg(g_userinfo->borrownum));
}

void ViewInformation::SetTableData()
{
    int count = 0;
    m_bcont = false;
    m_tablewidget->ClearTable();
    GraduationDesign* Grd = (GraduationDesign*)g_Graduation;
    ReturnInterface *ret = Grd->GetReturnInterface();
    std::vector<Borrowinfo> borrowVector;
    if (ret != NULL)
    {
        borrowVector = ret->GetBorrowinfoData();
    }
    QStringList list;
    for (int i = 0; i < borrowVector.size();i++)
    {
        list.clear();
        Bookinfo book = Grd->GetSaveBook(borrowVector[i].booknum);
        unsigned long outTime = borrowVector[i].borrowtime + 30 * 24 * 60 * 60 * (3 - borrowVector[i].renewalnum);
        QString str_out;
        if (outTime > borrowVector[i].nowtime)
        {
            str_out = "��";
        }
        else
        {
            str_out = "��";
        }
        QString str_borrow;
        if (borrowVector[i].returntime > borrowVector[i].borrowtime)
        {
            str_borrow = "�黹";
        }
        else
        {
            str_borrow = "����";
        }
        QDateTime qtime = QDateTime::fromTime_t(borrowVector[i].returntime);
        QString str_time = qtime.toString("yyyy-MM-dd");
        list << borrowVector[i].borrownum <<borrowVector[i].booknum << book.bookname << g_userinfo->usernum << g_userinfo->username << str_borrow << str_time << str_out;
        m_tablewidget->MySetItem(list);
    }
    m_bcont = true;
    m_count = 0;
}



void ViewInformation::OnDeleteBtnClick()
{
    QTcpSocket* Socket = (QTcpSocket*)g_Socket;
    if (Socket == NULL)
    {
        qDebug() << "�������ӳ���";
        return;
    }
    for (int i = 0; i < m_tablewidget->rowCount(); i++)
    {
        QString str = m_tablewidget->GetIndexText(i, 6);
        if (m_tablewidget->item(i, 0)->checkState() == Qt::Checked)
        {
            if (str == QString("����"))
            {
                m_tablewidget->item(i, 0)->setCheckState(Qt::Unchecked);
            }
            else
            {
                QString sendmsg = QString("{ \n"
                    "\"status\":\"5\",  \n"
                    "\"firstmsg\" : \"%1\",\n"
                    "\"secondmsg\" : \"%2\", \n"
                    "\"thirdmsg\" : \"3\", \n"
                    "\"fourthmsg\" :\"4\" };").arg(g_userinfo->usernum).arg(m_tablewidget->item(i, 1)->text());
                Socket->write(sendmsg.toUtf8());
            }
        }
    }
}

void ViewInformation::OnMenuBtnClick()
{
    QPoint pos;
    QRect rect;
    rect = m_MenuBtn->geometry();
    pos.setX(rect.x());
    pos.setY(rect.y() + rect.height());
    m_Menu->exec(this->mapToGlobal(pos));
}


void ViewInformation::OnSearchBooknaemAct()
{
    m_MenuBtn->SetText("�鼮����");
    m_MenuBtn->SetId(BOOKNAME);
}

void ViewInformation::OnSearchBooknumAct()
{
    m_MenuBtn->SetText("�鼮���");
    m_MenuBtn->SetId(BOOKNUM);
}

void ViewInformation::OnSearchCatagoryAct()
{
    m_MenuBtn->SetText("�鼮���");
    m_MenuBtn->SetId(CATAGORY);
}

void ViewInformation::OnSearchAuthorAct()
{
    m_MenuBtn->SetText("�鼮����");
    m_MenuBtn->SetId(AUTHOR);
}

void ViewInformation::OnSearchBtnClick()
{
    //for (int i = 0; i < m_tablewidget->rowCount(); i++)
    //{
    //    m_tablewidget->item(i, 0)->setCheckState(Qt::Checked);
    //}
    int count = 0;
    m_bcont = false;
    m_tablewidget->ClearTable();
    GraduationDesign* Grd = (GraduationDesign*)g_Graduation;
    ReturnInterface *ret = Grd->GetReturnInterface();
    std::vector<Borrowinfo> borrowVector;
    if (ret != NULL)
    {
        borrowVector = ret->GetBorrowinfoData();
    }
    QStringList list;
    for (int i = 0; i < borrowVector.size(); i++)
    {
        list.clear();
        Bookinfo book = Grd->GetSaveBook(borrowVector[i].booknum);
        if (!DLFUNC::SearchItem(book,m_SearchLed->text(),m_MenuBtn->GetId()))
        {
            continue;
        }
        unsigned long outTime = borrowVector[i].borrowtime + 30 * 24 * 60 * 60 * (3 - borrowVector[i].renewalnum);
        QString str_out;
        if (outTime > borrowVector[i].nowtime)
        {
            str_out = "��";
        }
        else
        {
            str_out = "��";
        }
        QString str_borrow;
        if (borrowVector[i].returntime > borrowVector[i].borrowtime)
        {
            str_borrow = "�黹";
        }
        else
        {
            str_borrow = "����";
        }
        QDateTime qtime = QDateTime::fromTime_t(borrowVector[i].returntime);
        QString str_time = qtime.toString("yyyy-MM-dd");
        list << borrowVector[i].borrownum << borrowVector[i].booknum << book.bookname << g_userinfo->usernum << g_userinfo->username << str_borrow << str_time << str_out;
        m_tablewidget->MySetItem(list);
    }
    m_bcont = true;
    m_count = 0;
}
