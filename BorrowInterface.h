#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QDateTime>
#include "DTableWidget.h"
#include "DPageBtn.h"
#include "DLineEdit.h"
#include "DLabel.h"
#include "DLFUNC.h"
#include "ReturnInterface.h"

class BorrowInterface : public QWidget
{
    Q_OBJECT

public:
    BorrowInterface(QWidget *parent = NULL);
    ~BorrowInterface();
    //��Ӧ�����������ݺ���
    void BorrowMsg(SocketMsg msg);
    void UpdateUserInfo();
    //�������ѡ�е�
    void ClearCheckItem();
private slots:
    void ViewDetail(QTableWidgetItem*); //˫��item�鿴����
    void CheckBoxChange(int, int);
    void ChangeBtnState(int);   //�ı���°�ť����ɫ
    void OnBorrowBtnClick();
    void OnSearchBtnClick();
    void OnScrollBarArriveBottom();
    void OnMenuBtnClick();
    void OnSearchBooknumAct();
    void OnSearchBooknaemAct();
    void OnSearchCatagoryAct();
    void OnSearchAuthorAct();
private:
    void InitGui();
    //���ĵ�diglog
    void BorrowRepeat(QString text);
    //���Ľ��������ͨ���������ķ�����ִ�У�
    void BorrowResult(SocketMsg msg,bool b = true);
    //�����Ƿ�ʧ�ܸı�checkboxѡ��״̬
    int  ChangeCheckBoxState(QString booknum);
    DTableWidget *m_tablewidget;
    QLabel      *m_NameLb;
    QLabel      *m_IDLb;
    DLabel      *m_NameShowLb;
    DLabel      *m_IDShowLb;
    QLabel      *m_BottomLb;
    DPageBtn    *m_BorrowBtn;
    DPageBtn    *m_SearchBtn;
    DPageBtn    *m_MenuBtn;
    QMenu       *m_Menu;
    DLineEdit   *m_SearchLed;
    QString     m_sqlwhere;
    std::vector<QString> m_CheckBookVector;//����ѡ�е��鼮���
    int  m_count;                //��¼��ѡ�����ж��ٸ�
    int m_bookcount;            //��¼�鼮һ�𵯳���ʾ
    bool m_bcont;               //�Ƿ����޸�m_count
    bool m_bSearch;
signals:
    void SigUserInfoUpdate();
};