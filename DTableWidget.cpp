#include "DTableWidget.h"

DTableWidget::DTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    setStyleSheet("QTableWidget{background:rgb(128,128,128,0); border: 1px solid rgb(128,128,128);\
                gridline-color : rgb(255, 215, 0);selection-background-color:rgb(255, 164, 52);}\
                QHeaderView::section {background-color:rgb(202,81,0,150);}\
        ");

//     this->horizontalScrollBar()->setStyleSheet(
//         "QScrollBar::handle:horizontal{background-color:rgb(193,206,219);}"
//         "QScrollBar::add-line:horizontal{width:0px;}"
//         "QScrollBar::sub-line:horizontal{width:0px;}"
//         "QScrollBar::left-arrow:horizontal,QScrollBar::right-arrow:horizontal{background-color:rgb(235,240,245);}"
//         "QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal {background:none;}"
//         );
    //setSelectionMode(QAbstractItemView::NoSelection); //ȡ����ѡ����ʽ�������ȡ��ѡ��
    //���ر�ͷ
    verticalHeader()->setVisible(false);
    //�����ʱ���Ա�ͷ�й�������ȡ���㣩
    horizontalHeader()->setHighlightSections(false);
    //���һ������Ӧ���
    horizontalHeader()->setStretchLastSection(true);
    //����ѡ�еķ�ʽ
    setSelectionBehavior(QAbstractItemView::SelectRows);
    //���ɱ༭
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    //����������
    setFocusPolicy(Qt::NoFocus);
    m_verticalBar = this->verticalScrollBar();
    //this->setVerticalScrollBar(m_verticalBar);
    m_verticalBar->setStyleSheet(
        "QScrollBar::vertical {border:0px ;width: 10px; margin:0px 0px 0px 0px;background-color:rgb(255,255,255);}"
        "QScrollBar::handle:vertical{background-color:rgb(193,206,219);}"
        "QScrollBar::add-line:vertical{width:0px;}"
        "QScrollBar::sub-line:vertical{width:0px;}"
        "QScrollBar::left-arrow:vertical,QScrollBar::right-arrow:vertical{background-color:rgb(235,240,245);}"
        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical {background:none;}"
        );
    connect(m_verticalBar, SIGNAL(valueChanged(int)), this, SLOT(Ontest(int)));
}

DTableWidget::~DTableWidget()
{

}

void DTableWidget::MySetItem(QStringList list)
{
    int temp = rowCount();
    insertRow(temp);
    QTableWidgetItem* check = new QTableWidgetItem();
    check->setCheckState(Qt::Unchecked);
    setItem(temp, 0, check);
    for (int i = 0; i < list.size();i++)
    {
        setItem(temp, i+1, new QTableWidgetItem(list.at(i)));
    }
}

QString DTableWidget::GetIndexText(int row, int column)
{
    QTableWidgetItem * item = this->item(row, column);
    return item->text();
}

void DTableWidget::DeletItem(int row)
{
    removeRow(row);
}

void DTableWidget::Ontest(int a)
{
    if (a == m_verticalBar->maximum())
    {
        emit OnScrollBarArriveBottom();
    }
}

void DTableWidget::ClearTable()
{
    while (rowCount())
    {
        removeRow(0);
    }
}

void DTableWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if ( event->button() == Qt::LeftButton)
    {
        qDebug() << tr("���˫������");
        QTableWidgetItem* item = itemAt(event->x(), event->y());
        //setCurrentItem(item); //����ѡ��״̬
        if ( NULL != item )
        {
            emit sendDoubleClickItem(item);
        }
    }
}
