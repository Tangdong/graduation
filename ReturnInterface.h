#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include "DTableWidget.h"
#include "DPageBtn.h"
#include "DLineEdit.h"
#include "DLabel.h"
#include "DLFUNC.h"
#include "comnQss.h"

class ReturnInterface : public QWidget
{
    Q_OBJECT

public:
    ReturnInterface(QWidget *parent = NULL);
    ~ReturnInterface();
    void ReturnMsg(SocketMsg msg);
    void ChangeBtnState(int);   //�ı���°�ť����ɫ
    void UpdateUserInfo();
    void SetTableData();
    bool IsReturn(QString booknum);        //�鼮�Ƿ��ڹ黹״̬
    std::vector<Borrowinfo> GetBorrowinfoData();
    void SetReturnTime(QString booknum,unsigned long returntime);//�黹������ͬ�����ı��صĻ�������
    void DeleteBorrowVectorItem(QString borrownum);//ɾ�����ر�������Ϣ
    Borrowinfo GetBorrowinfoItem(QString borrownum);//ͨ�����ı�Ż�ȡ��Ϣ
    Bookinfo GetBookinfoItem(QString borrownum);//ͨ�����ı�Ż�ȡ�鼮��Ϣ
private slots:
    void CheckBoxChange(int, int);
    void ViewDetail(QTableWidgetItem*); //˫��item�鿴����
    void OnReturnBtnClick();
    void OnSearchBtnClick();
    void OnMenuBtnClick();
    void OnSearchBooknumAct();
    void OnSearchBooknaemAct();
    void OnSearchCatagoryAct();
    void OnSearchAuthorAct();
private:
    void InitGui();
    void ReturnResult(SocketMsg msg,bool b);
    std::vector<Borrowinfo> m_borrowVector;//�������еĽ��ı����Ϣ
    DTableWidget* m_tablewidget;
    QLabel* m_NameLb;
    QLabel* m_IDLb;
    DLabel* m_NameShowLb;
    DLabel* m_IDShowLb;
    QLabel* m_BottomLb;
    DPageBtn* m_ReturnBtn;
    DPageBtn* m_MenuBtn;
    DPageBtn* m_SearchBtn;
    QMenu *m_Menu;
    DLineEdit* m_SearchLed;
    std::vector<QString> m_CheckBookVector;//����ѡ�е��鼮���
    int m_itemCount;
    int  m_count;                //��¼��ѡ�����ж��ٸ�
    bool m_bcont;               //�Ƿ����޸�m_count
signals:
    void SigUserInfoUpdate();
};
